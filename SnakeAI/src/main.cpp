#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "headers/isometric_map.hpp"

int main(int argc, char **argv)
{
  SDL_Renderer *win_renderer = nullptr;
  SDL_Window *window = nullptr;
  
  int map_width = 20;
  int map_height = 5;
  IsometricMap *i_map = new IsometricMap(map_width, map_height);

  // On initialise la SDL, s'il y a une erreur, l'initialisation renvoie 1
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    fprintf(stderr, "Erreur dans l'initialisation de SDL : %s\n", SDL_GetError());
    return 1;
  }

  // On initialise la librairie SDL_Image
  int flags = IMG_INIT_PNG;
  int init_status = IMG_Init(flags);
  if ((init_status & flags) != flags)
  {
    fprintf(stderr, "Erreur dans l'initialisation de la librairie SDL_Image au format PNG : %s\n", SDL_GetError());
    return 1;
  }

  // Création de la fenêtre
  window = SDL_CreateWindow("Isometric Tile Map", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 430, 300, SDL_WINDOW_SHOWN);

  // Vérification de la bonne création de la fenêtre
  if (!window)
  {
    fprintf(stderr, "Erreur dans la création de la fenêtre : %s\n", SDL_GetError());
    return 1;
  }

  // Création de la surface de rendu de la fenêtre
  win_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // On vérifie qu'on a bien récupérer les surfaces
  if (!win_renderer)
  {
    fprintf(stderr, "Erreur dans la création du rendu : %s\n", SDL_GetError());
    return 1;
  }

  // Chargement du tileset
  SDL_Surface *image = nullptr;
  image = IMG_Load("./res/isometric_tile_set_32x16.png");

  // Vérification du bon chargement de l'image
  if (!image)
  {
    fprintf(stderr, "Erreur dans le chargement de l'image : %s\n", SDL_GetError());
    return 1;
  }

  // Création d'une texture pour l'image
  SDL_Texture *tileset_img = SDL_CreateTextureFromSurface(win_renderer, image);
  
  // Variable de gestion des événements de la fenêtre
  SDL_Event event;
  bool game_run = true;
  
  // Game loop
  while (game_run)
  {
    // Gestion des événements
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT) 
        game_run = false;
    }

    // Affichage sur la fenêtre
    // On affiche un rectangle blanc
    //SDL_FillRect(win_surface, nullptr, SDL_MapRGB(win_surface->format, 255, 255, 255));
    SDL_SetRenderDrawColor(win_renderer, 255, 255, 255, 255); // On met la couleur d'affichage à blanc
    SDL_RenderClear(win_renderer); // On nettoie la fenêtre de rendu
    SDL_RenderDrawRect(win_renderer, nullptr); // On affiche le fond (un rectangle blanc)
  
    // Affichage de la carte
    i_map->display(win_renderer, tileset_img);

    //SDL_RenderCopy(win_renderer, tileset_img, &wanted_tile, &printed_tile);

    // On met à jour la fenêtre
    //SDL_UpdateWindowSurface(window);
    SDL_RenderPresent(win_renderer);
  }
  // On désinstancie la map
  delete i_map;

  // Destruction de la fenêtre
  SDL_DestroyWindow(window);

  // Destruction du rendu de la fenêtre
  SDL_DestroyRenderer(win_renderer);

  // Libération de la surface de l'image
  SDL_FreeSurface(image);

  // Libération de la texture
  SDL_DestroyTexture(tileset_img);

  // On quitte SDL
  SDL_Quit();

  // Fin de programme
  return 0;
}
