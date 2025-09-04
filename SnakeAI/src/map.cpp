#include "headers/map.hpp"

Map::Map(int width, int height)
{
  this->width = width; // largeur
  this->height = height; // longueur
  
  // On alloue le tilemap
  this->tilemap = new int* [height];
  for (int i = 0; i < height; i++)
    this->tilemap[i] = new int [width];
  
  // On remplis la carte
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      this->tilemap[i][j] = 0;
  
  // On met les murs
  for (int i = 0; i < width; i++)
  {
    this->tilemap[0][i] = 1;
    this->tilemap[height-1][i] = 1;
  }

  for (int i = 0; i < height; i++)
  {
    this->tilemap[i][0] = 1;
    this->tilemap[i][width-1] = 1;
  }
}

Map::~Map()
{
  for (int i = 0; i < this->height; i++)
    delete[] this->tilemap[i];
  delete[] this->tilemap;
}

void Map::set_blank()
{
  for (int i = 0; i < this->height; i++)
    for (int j = 0; j < this->width; j++)
      this->tilemap[i][j] = 0;
  
  for (int i = 0; i < this->width; i++)
  {
    this->tilemap[0][i] = 1;
    this->tilemap[this->height-1][i] = 1;
  }

  for (int i = 0; i < this->width; i++)
  {
    this->tilemap[i][0] = 1;
    this->tilemap[i][this->width-1] = 1;
  }
}

void Map::display()
{
  //printw("\x1b[0;0H");
  clear();
  for (int i = 0; i < this->height; i++)
  {
    for (int j = 0; j <this->width; j++)
      printw("%c ", this->tileset[this->tilemap[i][j]]);
      //printf("%d ", this->tilemap[i][j]);
    printw("\n");
  }
  refresh();
}

int Map::get_tile(Position pos)
{
  if (pos.x >= 0 && pos.x < this->width && pos.y >= 0 && pos.y < this->height)
    return this->tilemap[pos.y][pos.x];
  else
   return -1;
}

void Map::set_tile(Position pos, int value)
{
  if (pos.x >= 0 && pos.x < this->width && pos.y >= 0 && pos.y < this->height)
    this->tilemap[pos.y][pos.x] = value;
}
