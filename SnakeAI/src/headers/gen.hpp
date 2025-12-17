#pragma once

#include "game.hpp"
#include "dqnagent.hpp"

/**
 * @brief Fonction réalisant un algorithme génétique afin de déterminer les meilleurs paramètres pour entrainer l'agent de snake plus tard
 * @param net_shape: std::vector<int>, paramètre modifier par la fonction pour donner le meilleur le meilleur nombre de couches cachées avec le meilleur nombre de neurones par couches cachées pour le snake
 * @param learning_rate: float, modifier par la fonction pour avoir le meilleur taux d'apprentissage
 * @param epsilon: float, modifier par la fonction pour avoir le meilleur taux de décision
 * @param gamma: float, modifier par la fonction pour avoir le meilleur facteur d'importance d'apprentissage
 * @param batch_size: int, modifier par la fonction pour avoir la meilleur taille de mémoire d'apprentissage
 * @param memory_size: int, modifier par la fonction pour avoir la meilleur taille de mémoire globale
 * @param nb_gen: int, détermine combien ditérations doit réaliser l'algorithme
 * @param best_score: int, modifier par la fonction, contient le meilleur score obtenu par un agent
 * @param gen_best_score: int, modifier par la fonction, contient le numéro de la génération ayant réalisé le meilleur score
*/
void genetic_algorithm(std::vector<int> &net_shape, float &learning_rate, float &epsilon, float &gamma, int &batch_size, int &memory_size, int nb_gen, int &best_score, int &gen_best_score);
