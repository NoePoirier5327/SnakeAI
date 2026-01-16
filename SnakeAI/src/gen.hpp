#pragma once

/**
 * Fichier contenant la déclaration d'un algorithme génétique
 * en décembre 2025
 * par Noé Poirier
*/

#include "ai_engine/dqnagent.hpp"

/**
 * @brief Fonction réalisant un algorithme génétique afin de déterminer les meilleurs paramètres pour entrainer l'agent de snake plus tard
 * @param net_shape: std::vector<int>, paramètre modifié par la fonction pour donner le meilleur nombre de couches cachées avec le meilleur nombre de neurones par couches cachées pour le snake
 * @param learning_rate: float, modifié par la fonction pour avoir le meilleur taux d'apprentissage
 * @param epsilon: float, modifié par la fonction pour avoir le meilleur taux de décision
 * @param gamma: float, modifié par la fonction pour avoir le meilleur facteur d'importance d'apprentissage
 * @param batch_size: int, modifié par la fonction pour avoir la meilleure taille de mémoire d'apprentissage
 * @param memory_size: int, modifié par la fonction pour avoir la meilleure taille de mémoire globale
 * @param epsilon_decay: float, modifié par la fonction pour avoir le meilleur taux de baisse d'epsilon au cours du temps
 * @param epsilon_end: float, modifié par la fonction pour avoir la meilleure valeur d'epsilon après avoir convergé
 * @param convergence_counter: int, modifié par la fonction pour avoir le meilleur delai de convergence
 * @param nb_gen: int, détermine combien d'itérations doit réaliser l'algorithme
 * @param best_score: int, modifié par la fonction, contient le meilleur score obtenu par un agent
 * @param gen_best_score: int, modifié par la fonction, contient le numéro de la génération ayant réalisé le meilleur score
*/
void genetic_algorithm(std::vector<int> &net_shape, float &learning_rate, float &epsilon, float &gamma, int &batch_size, int &memory_size, float &epsilon_decay, float &epsilon_end, int &convergence_counter, int nb_gen, int &best_score, int &gen_best_score);
