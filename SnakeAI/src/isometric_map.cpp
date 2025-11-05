#include "headers/isometric_map.hpp"

IsometricMap::IsometricMap()
{
  // Allocation de la carte
  this->map = new Tile**[MAP_HEIGHT];
  for (int ligne = 0; ligne < MAP_HEIGHT; ligne++) this->map[ligne] = new Tile*[MAP_WIDTH];

  // Remplissage de la carte et ajout des coordonnées + instanciation des tuiles
  for (int ligne = 0; ligne < MAP_HEIGHT; ligne++)
    for (int colonne = 0; colonne < MAP_WIDTH; colonne++)
      this->map[ligne][colonne] = new Tile(t_floor, {colonne + 5, ligne});
}

IsometricMap::~IsometricMap()
{
  // on désintancie les tuiles
  for (int ligne = 0; ligne < MAP_HEIGHT; ligne++)
    for (int colonne = 0; colonne < MAP_WIDTH; colonne++)
      delete this->map[ligne][colonne];
  
  // on désintancie le tableau
  for (int ligne = 0; ligne < MAP_HEIGHT; ligne++)
    delete[] this->map[ligne];
  delete[] this->map;
}

void IsometricMap::modify(Position &pos, TileType value) { if (pos.x >= 0 && pos.x < MAP_WIDTH && pos.y >= 0 && pos.y < MAP_HEIGHT) this->map[pos.x][pos.y]->set_type(value); }

TileType IsometricMap::get_tile(Position& pos)
{
  if (pos.x >= 0 && pos.x < MAP_WIDTH && pos.y >= 0 && pos.y < MAP_HEIGHT) return this->map[pos.x][pos.y]->get_type();
  else return t_void;
}

void IsometricMap::display(SDL_Renderer *renderer, SDL_Texture *texture)
{
  // Affichage sur la fenêtre sdl
  for (int ligne = 0; ligne < MAP_HEIGHT; ligne++)
    for (int colonne = 0; colonne < MAP_WIDTH; colonne++)
      this->map[ligne][colonne]->display(renderer, texture);
}

void IsometricMap::set_blank()
{
  for (int ligne = 0; ligne < MAP_HEIGHT; ligne++)
    for (int colonne = 0; colonne < MAP_WIDTH; colonne++)
      this->map[ligne][colonne]->set_type(t_floor);
}
