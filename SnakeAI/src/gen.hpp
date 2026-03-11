#pragma once

/**
 * Fichier contenant la déclaration d'un algorithme génétique
 * en décembre 2025
 * par Noé Poirier
*/

#include "ai_engine/dqnagent.hpp"

#include <SDL2/SDL_render.h>


/**
 * @brief Type contenant l'ensemble des paramètres d'un seul agent.
*/
struct AgentParams
{
  std::vector<int> net_shape;
  float learning_rate;
  float epsilon;
  float gamma;
  int batch_size;
  int memory_size;
  float epsilon_decay;
  float epsilon_end;
  int convergence_counter;
};


/**
 * @brief Fonction réalisant un algorithme génétique afin de déterminer les meilleurs paramètres pour entrainer l'agent de snake plus tard
 * @param population: int, population par génération d'agents d'apprentissage
 * @param nb_gen: int, détermine combien d'itérations doit réaliser l'algorithme
 * @param renderer: SDL_Renderer, fenêtre de rendue sur laquelle afficher les agents en train de s'entrainer
 * @return AgentParams, paramètres calculé par l'algorithme
*/
AgentParams genetic_algorithm(const int &population, const int& nb_gen, SDL_Renderer *renderer);
