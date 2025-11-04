#include "headers/tile.hpp"
#include "headers/global.hpp"

Tile::Tile(TileType value, Position pos)
{
  this->type = value;

  // Calcule des coordonnées isométriques
  this->pos.x = (pos.x - pos.y) * (TILE_WIDTH / 2);
  this->pos.y = (pos.x + pos.y) * (TILE_HEIGHT / 2);
  
  // Tile du sol
  this->wanted_tile[0].x = 32;
  this->wanted_tile[0].y = 16;
  this->wanted_tile[0].w = 32;
  this->wanted_tile[0].h = 16;

  // tile du serpent
  this->wanted_tile[1].x = 0;
  this->wanted_tile[1].y = 0;
  this->wanted_tile[1].w = 32;
  this->wanted_tile[1].h = 16;

  // tile de la pomme
  this->wanted_tile[2].x = 0;
  this->wanted_tile[2].y = 16;
  this->wanted_tile[2].w = 32;
  this->wanted_tile[2].h = 16;
}

void Tile::display(SDL_Renderer *renderer, SDL_Texture *texture)
{
  //SDL_Rect rect = {pos_x * this->tile_width, pos_y * this->tile_height, this->tile_width, this->tile_height};
  //SDL_RenderFillRect(renderer, &rect);
  SDL_Rect rect = {this->pos.x, this->pos.y, TILE_WIDTH, TILE_HEIGHT};
  SDL_RenderCopy(renderer, texture, &this->wanted_tile[this->type], &rect);
}

TileType Tile::get_type() { return this->type; }

void Tile::set_type(TileType value) { this->type = value; }

void Tile::set_coords(Position pos)
{
  this->pos.x = (pos.x - pos.y) * (TILE_WIDTH / 2);
  this->pos.y = (pos.x + pos.y) * (TILE_HEIGHT / 2); 
}
