#pragma once

/**
 * Fichier contenant les valeurs et fonctions utilisées partout dans le projet
 * en 2025
 * par Noé Poirier
*/

#include <vector>
#include <random>

const static int MAP_WIDTH = 10;
const static int MAP_HEIGHT = 10;
const static int EXPLORATION_LIMIT = 10000;

/**
 * @brief Structure gérant les positions sur la carte
*/
struct Position
{
  int x;
  int y;
};

