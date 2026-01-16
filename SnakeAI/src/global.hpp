#pragma once

/**
 * Fichier contenant les valeurs et fonctions utilisées partout dans le projet
 * en 2025
 * par Noé Poirier
*/

#include <vector>
#include <random>

const static int MAP_WIDTH = 6;
const static int MAP_HEIGHT = 6;
const static int EXPLORATION_LIMIT = 10000;

/**
 * @brief structure gérant les positions sur la carte
*/
struct Position
{
  int x;
  int y;
};

