#pragma once

#include <vector>
#include <random>

/**
 * @brief Fonction permettant la génération d'un nombre aléatoire entre deux bornes
 * @param min:double, borne minimale pour la génération aléatoire
 * @param max:double, borne maximale pour la génération aléatoire
 * @return double, nombre aléatoire généré par la fonction
*/
double rng(double min, double max);

double* v_max(std::vector<double> a);

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
