#pragma once

/**
 * Fichier contenant les valeurs et fonctions utilisées partout dans le projet
 * en 2025
 * par Noé Poirier
*/

#include <vector>
#include <random>

// Utilisé dans snake.cpp et main.cpp, d'où sa place ici
const static int MAP_WIDTH = 10;
const static int MAP_HEIGHT = 10;

// Utilisé dans main.cpp et game.cpp, d'où sa place ici
const static int WIN_WIDTH = 600;
const static int WIN_HEIGHT = 400;

const static int EXPLORATION_LIMIT = 10000;

/**
 * @brief Structure gérant les positions sur la carte
*/
struct Position
{
  int x;
  int y;
};

