#include "headers/apple.hpp"

Apple::Apple(int height, int width)
{
  this->pos.x = (rand() % (width - 2)) + 1;
  this->pos.y = (rand() % (height - 2)) + 1;
}

Position Apple::get_pos() { return this->pos; }
