#include "headers/isometric_map.hpp"

IsometricMap::IsometricMap(int &map_width, int &map_height)
{
  this->map_width = map_width;
  this->map_height = map_height;

  // Allocation de la carte
  this->map = new Tile**[this->map_height];
  for (int ligne = 0; ligne < this->map_height; ligne++) this->map[ligne] = new Tile*[this->map_width];

  // Remplissage de la carte et ajout des coordonnées + instanciation des tuiles
  for (int ligne = 0; ligne < this->map_height; ligne++)
    for (int colonne = 0; colonne < this->map_width; colonne++)
      this->map[ligne][colonne] = new Tile(t_floor, 32, 16, {colonne + 5, ligne});
}

IsometricMap::~IsometricMap()
{
  // on désintancie les tuiles
  for (int ligne = 0; ligne < this->map_height; ligne++)
    for (int colonne = 0; colonne < this->map_width; colonne++)
      delete this->map[ligne][colonne];
  
  // on désintancie le tableau
  for (int ligne = 0; ligne < this->map_height; ligne++)
    delete[] this->map[ligne];
  delete[] this->map;
}

void IsometricMap::modify(Position &pos, TileType value) { if (pos.x >= 0 && pos.x < this->map_width && pos.y >= 0 && pos.y < this->map_height) this->map[pos.x][pos.y]->set_type(value); }

TileType IsometricMap::get_tile(Position& pos)
{
  if (pos.x >= 0 && pos.x < this->map_width && pos.y >= 0 && pos.y < this->map_height) return this->map[pos.x][pos.y]->get_type();
  else return t_void;
}

void IsometricMap::display(SDL_Renderer *renderer, SDL_Texture *texture)
{
  // Affichage sur la fenêtre sdl
  for (int ligne = 0; ligne < this->map_height; ligne++)
    for (int colonne = 0; colonne < this->map_width; colonne++)
      this->map[ligne][colonne]->display(renderer, texture);
}
