/**
 * Fichier contenant l'implémentation du serpent du jeu snake
 * en 2025
 * par Noé Poirier
*/

#include "snake.hpp"

const static Direction DIRECTIONS[4] = {haut, bas, gauche, droite};

Snake::Snake()
{
  // On place le serpent n'importe où sur la carte
  this->pos.push_back({(rand() % (MAP_WIDTH - 1)) + 1, (rand() % (MAP_HEIGHT - 1)) + 1});

  // On définit sa première direction de manière aléatoire
  this->direction = DIRECTIONS[rand() % 4];
}

bool Snake::is_not_opposite_of_last_direction(const Direction &direction)
{
  if (direction == haut && this->direction == bas) return false;
  if (direction == bas && this->direction == haut) return false;
  if (direction == gauche && this->direction == droite) return false;
  if (direction == droite && this->direction == gauche) return false;
  return true;
}

void Snake::move()
{
  Position temp = this->pos[0];

  switch (this->direction)
  {
    case haut:
      temp.y --;
      break;

    case bas:
      temp.y ++;
      break;

    case gauche:
      temp.x --;
      break;

    case droite:
      temp.x ++;
      break;
  }

  this->pos.pop_back();
  this->pos.insert(this->pos.begin(), temp);
}

void Snake::set_direction(const Direction &direction)
{
  // Si la nouvelle direction est l'opposé de l'ancienne, alors on garde l'ancienne
  if (this->is_not_opposite_of_last_direction(direction))
    this->direction = direction;
}

void Snake::eat_apple()
{
  Position temp = this->pos[this->pos.size() - 1];

  switch (this->direction)
  {
    case haut:
      temp.y ++;
      break;

    case bas:
      temp.y --;
      break;

    case gauche:
      temp.x ++;
      break;

    case droite:
      temp.x --;
      break;
  }

  this->pos.push_back(temp);
}

std::vector<Position>& Snake::get_pos() { return this->pos; }
