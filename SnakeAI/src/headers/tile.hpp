#pragma once

#include <SDL2/SDL.h>
#include "global.hpp"

enum TileType
{
  t_void = -1,
  t_floor = 0,
  t_snake = 1,
  t_apple = 2
};

/**
  * @brief Classe gérant le fonctionnement général d'une tuile de la carte (affichage et gestion de valeur associée)
*/
class Tile
{
  public:
    /**
     * @brief Constructeur de la tuile courante, sa position sera 0, 0 par défaut
     * @param value:TileType, valeur associée à la tuile courante (il s'agit de son type)
     * @param tile_width:int, largeur de la tuile courante
     * @param tile_height:int, hauteur de la tuile courante
     * @param pos: Position en x et y de la tuile, par défaut à 0, 0
    */
    Tile(TileType value, int tile_width, int tile_height, Position pos = {0, 0});
    
    /**
     * @brief Méthode permettant l'affichage de la tuile courante sur la fenêtre SDL
     * @param renderer:SDL_Renderer, instance de rendu de la fenêtre SDL
     * @param texture:SDL_Texture, instance de texture du tileset
    */
    void display(SDL_Renderer *renderer, SDL_Texture *texture);
    
    /**
     * @brief Méthode permettant de récupérer le type de la tuile courante
     * @return TileType, type de la tuile courante
    */
    TileType get_type();
    
    /**
     * @brief Mutateur du type de la tuile courante
     * @param value:TileType, nouveau type à attribuer
    */
    void set_type(TileType value);
    
    /**
     * @brief Mutateur des coordonnées de la tuile courante
     * @param pos: Position, nouvelle position de la tuile
    */ 
    void set_coords(Position pos);
    
  private:
    TileType type; // valeur associée à la tuile courante
    int tile_width; // largeur de la tuile
    int tile_height; // hauteur de la tuile
    Position pos; // Position de la tuile
    SDL_Rect wanted_tile[4]; // Assets des tiles
};
