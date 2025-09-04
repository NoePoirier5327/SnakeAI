#include "headers/snake.hpp"

Snake::Snake(int height, int width)
{
  Position temp;
  temp.x = (rand() % (width - 2)) + 1;
  temp.y = (rand() % (height - 2)) + 1;

  this->pos.push_back(temp);
  this->direction = (rand() % (4));
}

void Snake::move(int direction)
{
  Position temp = this->pos[0];

  switch (direction)
  {
    case 0:
      temp.y --;
      break;

    case 1:
      temp.y ++;
      break;

    case 2:
      temp.x --;
      break;

    case 3:
      temp.x ++;
      break;

    default:
      break;
  }

  this->pos.pop_back();
  this->pos.insert(this->pos.begin(), temp);
}

void Snake::eat_apple()
{
  Position temp = this->pos[this->pos.size() - 1];

  switch (this->direction)
  {
    case 0:
      temp.y ++;
      break;

    case 1:
      temp.y --;
      break;

    case 2:
      temp.x ++;
      break;

    case 3:
      temp.x --;
      break;

    default:
      break;
  }

  this->pos.push_back(temp);
}


std::vector<Position> Snake::get_pos() { return this->pos; }
