#pragma once

#include "global.hpp"
#include <cstdlib>

/**
 * @brief Classe gérant le fonctionnement de la pomme du jeu snake
*/
class Apple
{
  public:
    /**
     * @brief Constructeur de la classe, détermine la position aléatoire de la pomme
     * @param height: int, hauteur de la carte en tile, permet de générer la position de la pomme
     * @param width: int, largeur de la carte en tile, permet de générer la position de la pomme
    */
    Apple(int height, int width);

    /**
     * @brief Accesseur de la position de la pomme
     * @return Position, position de la pomme
    */
    Position get_pos();

  private:
    Position pos; // position de la pomme
};
