#pragma once

/**
 * Fichier contenant la déclaration d'un agent d'apprentissage profond
 * en 2025
 * par Noé Poirier
*/

#include "mlp.hpp"

#include <algorithm>
#include <cmath>

struct Episodes
{
  std::vector<double> state;
  std::vector<double> next_state;
  float reward;
  int action;
  bool done;
};

/**
 * @brief Classe gérant un agent d'apprentissage profond
*/
class DQNAgent
{
  public:
    /**
     * @brief Constructeur de l'agent d'apprentissage
     * @param net_shape: std::vector<int>&, forme globale du réseau de neurone associé
     * @param lr: float, taux d'apprentissage de l'agent, par défaut 0.01
     * @param epsilon: float, taux d'exploration, par défaut à 1.0
     * @param gamma: float, taux de pertinence des récompenses, par défaut 0.95
     * @param batch_size: int, taille de l'échantillon d'entrainement, par défaut à 256
     * @param max_memory_size: int, taille maximale de la mémoire d'actions globale, par défaut à 100000
     * @param epsilon_decay: float, taux de baisse d'epsilon dans le temps, par défaut à 0.95
     * @param epsilon_end: float, valeur limite d'epsilon pour l'algorithme epsilon decay, par défaut à 0.05
     * @param convergence_counter: int, valeur empêchant epsilon de converger trop vite, par défaut à 100
    */
    DQNAgent(const std::vector<int>& net_shape, const float &lr = 0.001, const float &epsilon = 1.0, const float &gamma = 0.95, const int &batch_size = 256, const int &max_memory_size = 100000, const float &epsilon_decay = 0.95, const float &epsilon_end = 0.05, const int &convergence_counter = 100);
    
    /**
     * @brief Destructeur de l'agent courant
    */
    ~DQNAgent();
    
    /**
     * @brief Méthode permettant à l'agent de décider d'une action en fonction d'un état donné
     * @param state: std::vector<double>&, état à partir duquel l'agent doit décider d'une action
     * @return int, choix de l'agent
    */
    int decide(std::vector<double>& state);

    /**
     * @brief Méthode permettant d'entrainer l'agent et le réseau de neurone associé à court term
     * @param state: std::vector<double>&, état courant de l'environnement
     * @param reward: float, récompense de l'agent, positive comme négative
     * @param next_state: std::vector<double>&, prochain état de l'environnement
     * @param done: bool, permet de savoir si l'environnement est dans son état final ou non
     * @param store_memory: bool, permet de savoir si on va stocker les états en paramètres dans la mémoire de l'agent, true par défaut
    */
    void train_short_term(std::vector<double>& state, float reward, std::vector<double>& next_state, bool done, bool store_memory = true);

    /**
     * @brief Méthode permettant d'entrainer l'agent sur un ensemble de données quelconque ammacées au fur et à mesure du jeu, on suppose qu'on a assez d'élément pour créer un jeu de test
    */
    void train_long_term();
    
    /**
     * @brief Accesseur de l'itération courante du réseau (nombre de fois ou il a perdu dans la partie)
     * @return int, itération courante
    */
    int get_current_iteration();

    /**
     * @brief Mutateur de la taille de l'échantillon mémoire sur lequel entrainer l'agent
     * @param batch_size : int, nouvelle taille d'échantillon d'entrainement
     */
    void set_batch_size(const int &batch_size);

  private:  
    float learning_rate;            // taux d'apprentissage du réseau de neurone
    float epsilon;                  // taux facteur décisionnel de l'agent
    float gamma;                    // taux de pertinence des récompenses

    float epsilon_end;              // valeur limite atteignable par l'algorithme epsilon_decay
    float epsilon_decay;            // taux de baisse d'epsilon dans le temps
    int convergence_counter;        // valeur permettant de gérer la vitesse de baisse d'epsilon dans le temps
    
    int iteration;
  
    std::vector<Episodes>* memory;  // Mémoire de l'agent qui sert de banque d'apprentissage pour l'entrainement à long terme
    int batch_size;                 // Taille de l'échantillon mémoire sur lequel entrainer l'agent courant
    int max_memory_size;            // Taille max de la mémoire d'actions

    MLP *mlp;                       // réseau de neurone multicouche associé à l'agent
    MLP *target_network;            // réseau cible pour stabiliser l'apprentissage

    int action;                     // dernière action de l'agent
    int nb_action;                  // nombre d'actions réalisable par l'agent
};
