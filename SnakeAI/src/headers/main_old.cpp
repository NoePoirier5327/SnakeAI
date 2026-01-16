#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

#include <csignal>
#include <iostream>
#include <string>

#include "headers/game.hpp"
#include "headers/dqnagent.hpp"

int main(int argc, char **argv)
{
  // Initalisation de la fenêtre de rendu
  SDL_Renderer *win_renderer = nullptr;
  SDL_Window *window = nullptr;
  
  // Initalisation du jeu
  Game *i_game = new Game();
  
  // Initalisation de l'agent d'apprentissage
  std::vector<int> net_shape = {77, 128, 64, 4};
  DQNAgent *bob = new DQNAgent(net_shape);

  // Vecteurs servant à l'entrainement de l'agent en stockant les états du jeu
  std::vector<double> state;
  std::vector<double> next_state;

  int best_score = 0;
  int best_iteration = 1;

  // On initialise la SDL, s'il y a une erreur, l'initialisation renvoie 1
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "Erreur dans l'initialisation de SDL : " << SDL_GetError() << std::endl;
    return 1;
  }

  // On initialise la bibliothèque TTF
  if (TTF_Init() == -1)
  {
    std::cerr << "Erreur dans l'initialisation de SDL_TTF : " << SDL_GetError() << std::endl;
    SDL_Quit();
    return -1;
  }

  TTF_Font *font = TTF_OpenFont("res/0xProtoNerdFont-Bold.ttf", 25);
  SDL_Color font_color = {255, 255, 255};
  SDL_Surface *txt_surface = nullptr;
  std::string text; SDL_Rect txt_rect = {0, 0, 0, 0};
  SDL_Texture *txt_texture = nullptr;

  // On initialise la librairie SDL_Image
  int flags = IMG_INIT_PNG;
  int init_status = IMG_Init(flags);
  if ((init_status & flags) != flags)
  {
    std::cerr << "Erreur dans l'initialisation de la librairie SDL_Image au format PNG : " << SDL_GetError() << std::endl;
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  // Création de la fenêtre
  window = SDL_CreateWindow("SnakeAI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);

  // Vérification de la bonne création de la fenêtre
  if (!window)
  {
    std::cerr << "Erreur dans la création de la fenêtre : " << SDL_GetError() << std::endl;
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  // Création de la surface de rendu de la fenêtre
  win_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // On vérifie qu'on a bien récupérer les surfaces
  if (!win_renderer)
  {
    std::cerr << "Erreur dans la création du rendu : " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  // Chargement du tileset
  SDL_Surface *image = nullptr;
  image = IMG_Load("./res/isometric_snake.png");

  // Vérification du bon chargement de l'image
  if (!image)
  {
    std::cerr << "Erreur dans le chargement de l'image : " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(win_renderer);
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  // Création d'une texture pour l'image
  SDL_Texture *tileset_img = SDL_CreateTextureFromSurface(win_renderer, image);
  
  // Variable de gestion des événements de la fenêtre
  SDL_Event event;

  bool run = true;
  
  // Game loop
  while (run)
  {
    // Gestion des événements
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT) 
        run = false;

      if (event.type == SDL_KEYDOWN)
        if (event.key.keysym.sym == SDLK_ESCAPE)
          run = false;
    }
    
    // On fait décider l'agent d'apprentissage
    state = i_game->get_game_state();
    i_game->handle_inputs(bob->decide(state));
    i_game->update();

    // Affichage sur la fenêtre
    // On affiche un rectangle blanc
    SDL_SetRenderDrawColor(win_renderer, 0, 0, 0, 255); // On met la couleur d'affichage à blanc
    SDL_RenderClear(win_renderer); // On nettoie la fenêtre de rendu
    SDL_RenderDrawRect(win_renderer, nullptr); // On affiche le fond (un rectangle blanc)
  
    // Affichage de la carte
    i_game->display(win_renderer, tileset_img);

    // Affichage du text
    text = "Iteration : " + std::to_string(bob->get_current_iteration()) + " | Best : " + std::to_string(best_score);
    txt_surface = TTF_RenderText_Blended(font, text.c_str(), font_color);
    txt_texture = SDL_CreateTextureFromSurface(win_renderer, txt_surface);
    SDL_QueryTexture(txt_texture, nullptr, nullptr, &txt_rect.w, &txt_rect.h);

    // On met à jour la fenêtre
    SDL_RenderCopy(win_renderer, txt_texture, nullptr, &txt_rect);
    SDL_RenderPresent(win_renderer);

    // On libert la mémoire de la texture et de la surface de rendu du texte
    SDL_FreeSurface(txt_surface); txt_surface = nullptr;
    SDL_DestroyTexture(txt_texture); txt_texture = nullptr;

    // On entraine l'agent d'apprentissage en fonction de ses actions
    next_state = i_game->get_game_state();

    if (i_game->get_score() > best_score)
    {
      best_score = i_game->get_score();
      best_iteration = bob->get_current_iteration();
    }

    if (i_game->the_snake_ate_an_apple()) bob->train_short_term(state, 10, next_state, i_game->game_over);
    else if (i_game->game_over)
    {
      bob->train_short_term(state, -1, next_state, i_game->game_over);
      delete i_game;
      i_game = new Game();
      
      // L'agent a fini une génération, on l'entraine sur sa mémoire global
      bob->train_long_term();
    }
    else bob->train_short_term(state, -0.1, next_state, i_game->game_over);
  }

  // On affiche la dernière partie de l'agent à une vitesse compréhensible par l'homme
  run = true;
  while (run)
  {
    state = i_game->get_game_state();
    i_game->handle_inputs(bob->decide(state));
    i_game->update();

    SDL_SetRenderDrawColor(win_renderer, 0, 0, 0, 255);
    SDL_RenderClear(win_renderer);
    SDL_RenderDrawRect(win_renderer, nullptr);

    SDL_Delay(100);

    i_game->display(win_renderer, tileset_img);

    text = "Iteration : " + std::to_string(bob->get_current_iteration()) + " | Best : " + std::to_string(best_score);
    txt_surface = TTF_RenderText_Blended(font, text.c_str(), font_color);
    txt_texture = SDL_CreateTextureFromSurface(win_renderer, txt_surface);
    SDL_QueryTexture(txt_texture, nullptr, nullptr, &txt_rect.w, &txt_rect.h);

    SDL_RenderCopy(win_renderer, txt_texture, nullptr, &txt_rect);
    SDL_RenderPresent(win_renderer);

    SDL_FreeSurface(txt_surface); txt_surface = nullptr;
    SDL_DestroyTexture(txt_texture); txt_texture = nullptr;

    if (i_game->game_over)
      run = false;
  }

  std::cout << "Le meilleur score réaliser par l'IA est de " << best_score << ", à l'itération " << best_iteration << std::endl;
  std::cout << "Dernière itération -> " << bob->get_current_iteration() << std::endl;

  // On désinstancie le jeu et l'agent d'apprentissage
  delete i_game;
  delete bob;

  // Destruction de la fenêtre
  SDL_DestroyWindow(window);

  // Destruction du rendu de la fenêtre
  SDL_DestroyRenderer(win_renderer);

  // Libération de la surface de l'image
  SDL_FreeSurface(image);

  // Libération de la texture
  SDL_DestroyTexture(tileset_img);

  TTF_CloseFont(font);

  // On quitte SDL
  TTF_Quit();
  SDL_Quit();

  // Fin de programme
  return 0;
}
