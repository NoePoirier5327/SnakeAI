#pragma once

#include "global.hpp"
#include <cstdlib>

class Apple
{
  public:
    Apple(int height, int width);
    Position get_pos();

  private:
    Position pos;
};
