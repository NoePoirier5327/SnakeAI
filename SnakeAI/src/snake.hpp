#pragma once

/**
 * Fichier contenant la déclaration d'une classe gérant un Serpent du jeu Snake
 * en 2025
 * par Noé Poirier
*/

#include "global.hpp"

#include <vector>
#include <cstdlib>
#include <iostream>

/**
 * @brief Type énuméré gérant la direction du serpent sur le plan
*/
enum Direction
{
  haut = 0,
  bas = 1,
  gauche = 2,
  droite = 3
};

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
     * @brief Méthode déplaçant le serpent en fonction de sa direction courante
    */
    void move();

    /**
     * @brief Mutateur de la direction du serpent.
     * @param direction : Direction, nouvelle direction du serpent
     */
    void set_direction(const Direction &direction);

    /**
     * @brief Méthode permettant de faire grandir le serpent d'une unité de taille
    */
    void eat_apple();

    /**
     * @brief Accesseur du vecteur pôsition du serpent
     * @return std::vector<Position>&, vecteur contenant les pôsitions des parties du corp du serpent
    */
    std::vector<Position>& get_pos();
    
  private:
    /**
     * @brief Méthode permettant de vérifier que la direction en paramètre n'est pas l'opposé de la dernière direction
     * @param direction: Direction, direction à vérifier
     * @return bool, si true, la direction est l'opposé de la dernière, false sinon
    */
    bool is_not_opposite_of_last_direction(const Direction &direction);

    std::vector<Position> pos; // vecteur contenant les positions des parties du corp du serpent
    Direction direction; // dernière direction du serpent
};
