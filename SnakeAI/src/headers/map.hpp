#pragma once

#include <ncurses.h>
#include "global.hpp"

class Map
{
  public:
    Map(int height, int width);
    ~Map();

    void display();

    int get_tile(Position pos);

    void set_tile(Position pos, int value);
    
    void set_blank();

  private:
    int **tilemap;
    int width;
    int height;
    char tileset[6] = " EASH";
};
