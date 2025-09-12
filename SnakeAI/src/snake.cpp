#include "headers/snake.hpp"

Snake::Snake(int height, int width)
{
  Position temp;
  //temp.x = (rand() % (width - 2)) + 1;
  //temp.y = (rand() % (height - 2)) + 1;
  temp.x = int_rng(1, width-1);
  temp.y = int_rng(1, height-1);

  this->pos.push_back(temp);
  //this->direction = (rand() % (4));
  this->direction = int_rng(0, 3);
}

bool Snake::is_not_opposite_of_last_direction(int direction)
{
  if (direction == 0 && this->direction == 1) return false;
  if (direction == 1 && this->direction == 0) return false;
  if (direction == 2 && this->direction == 3) return false;
  if (direction == 3 && this->direction == 2) return false;
  return true;
}

void Snake::move(int direction)
{
  Position temp = this->pos[0];

  switch (this->direction)
  {
    case 0: // Haut
      temp.y --;
      break;

    case 1: // Bas
      temp.y ++;
      break;

    case 2: // Gauche
      temp.x --;
      break;

    case 3: // Droite
      temp.x ++;
      break;

    default:
      break;
  }
  
  // Si la nouvelle direction est l'opposé de la nouvelle, on conserve la précédente
  if (this->is_not_opposite_of_last_direction(direction))
    this->direction = direction;

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

std::vector<Position>& Snake::get_pos() { return this->pos; }
