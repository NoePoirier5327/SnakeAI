#pragma once

#include <vector>
#include <random>

const static int WIN_WIDTH = 900;
const static int WIN_HEIGHT = 600;
const static int MAP_WIDTH = 12;
const static int MAP_HEIGHT = 12;
const static int TILE_WIDTH = 64;
const static int TILE_HEIGHT = 32;

/**
 * @brief Fonction permettant la génération d'un nombre aléatoire entre deux bornes
 * @param min:double, borne minimale pour la génération aléatoire
 * @param max:double, borne maximale pour la génération aléatoire
 * @return double, nombre aléatoire généré par la fonction
*/
double rng(double min, double max);

/**
 * @brief Fonction générant un nombre aléatoire entier entre deux bornes entières
 * @param min: int, borne minimale
 * @param max: int, borne maximale
 * @return int, nombre aléatoire généré par la fonction
*/
int int_rng(int min, int max);

/**
 * @brief Fonction d'acitvation des neurones
 * @param x: double, valeur à activer
 * @return double, valeur activée
*/
double f(double x);

/**
 * @brief dérivée de la fonction d'activation des neurone (utilisé pour l'apprentissage en règle général)
 * @param x: double, valeur à activer
 * @return double, valeur activée
*/
double f_prime(double x);

/**
 * @brief structure gérant les positions sur la carte
*/
struct Position
{
  int x;
  int y;
};

