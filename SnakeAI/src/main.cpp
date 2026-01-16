/**
 * Fichier principale du projet
 * en 2025
 * par Noé Poirier
*/

#include "game.hpp"

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <ctime>

int main()
{
  // On initialise la graine aléatoire sur l'heure actuelle
  srand(time(nullptr));

	// Initialisation de la fenêtre de rendu
  SDL_Renderer *win_renderer = nullptr;
  SDL_Window *window = nullptr;

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

  // On vérifie qu'on a bien récupéré les surfaces
  if (!win_renderer)
  {
    std::cerr << "Erreur dans la création du rendu : " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 1;
  }

  Game *game = new Game(win_renderer);
  
  // Variable de gestion des événements de la fenêtre
  SDL_Event event;

  bool run = true;
  
  // Game loop
  while (run)
  {
    SDL_Delay(500);

    // Gestion des événements
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT) 
        run = false;

      if (event.type == SDL_KEYDOWN)
        switch (event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            run = false;
            break;

          case SDLK_UP:
            game->handle_inputs(haut);
            break;

          case SDLK_DOWN:
            game->handle_inputs(bas);
            break;

          case SDLK_LEFT:
            game->handle_inputs(gauche);
            break;

          case SDLK_RIGHT:
            game->handle_inputs(droite);
            break;

          default:
            break;
        }
    }

    game->update();

    // Affichage sur la fenêtre
    // On affiche un rectangle blanc
    SDL_SetRenderDrawColor(win_renderer, 0, 0, 0, 255); // On met la couleur d'affichage à noir
    SDL_RenderClear(win_renderer); // On nettoie la fenêtre de rendu
    SDL_RenderDrawRect(win_renderer, nullptr); // On affiche le fond (un rectangle blanc)
    
    game->display(win_renderer);

    // On met à jour la fenêtre
    SDL_RenderPresent(win_renderer);
  }

  delete game;

  // Destruction de la fenêtre et de la surface de rendue
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(win_renderer);

  // On quitte SDL
  TTF_Quit();
  SDL_Quit();

  // Fin de programme
  return 0;
}