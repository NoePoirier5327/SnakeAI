#pragma once

#include "global.hpp"
#include <vector>
#include <cstdlib>

class Snake
{
  public:
    Snake(int height, int width);

    void move(int direction);

    void eat_apple();

    std::vector<Position> get_pos();
    
  private:
    std::vector<Position> pos;
    int direction;
};
