#pragma once

#include "global.hpp"
#include <vector>
#include <cstdlib>
#include <iostream>

/**
 * @brief Classe permettant de gérer le serpent
*/
class Snake
{
  public:
    /**
     * @brief Constructeur du serpent, détermine sa position de manière aléatoire
    */
    Snake();
    
    /**
     * @brief Méthode déplaçant le serpent en fonction d'une direction donnée
     * @param direction: int, 0 haut, 1 bas, 2 gauche, 3 droite
    */
    void move(int direction);

    /**
     * @brief Méthode permettant de faire grandir le serpent d'une unité de taille
    */
    void eat_apple();

    /**
     * @brief Acceseur du vecteur pôsition du serpent
     * @return std::vector<Position>&, vecteur contenant les pôsitions des parties du corp du serpent
    */
    std::vector<Position>& get_pos();
    
  private:
    /**
     * @brief Méthode permettant de vérifier que la direction en paramètre n'est pas l'opposé de la dernière direction
     * @param direction: int, direction à vérifier
     * @return bool, si true, la direction est l'opposé de la dernière, false sinon
    */
    bool is_not_opposite_of_last_direction(int direction);

    std::vector<Position> pos; // vecteur contenant les positions des parties du corp du serpent
    int direction; // dernière direction du serpent
};
