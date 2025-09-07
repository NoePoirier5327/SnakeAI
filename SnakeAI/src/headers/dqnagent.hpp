#pragma once

#include "mlp.hpp"
#include <algorithm>

/**
 * @brief Classe gérant un agent d'apprentissage profond
*/
class DQNAgent
{
  public:
    /**
     * @brief Constructeur de l'agent d'apprentissage
     * @param net_shape: std::vector<int>, forme globale du réseau de neurone associé
     * @param nb_action: int, nombre de choix à disposition de l'agent
     * @param lr: double, taux d'apprentissage de l'agent, par défaut 0.01
     * @param epsilon: double, taux de décision de l'agent, par défaut 0.2
     * @param gamma: double, taux de pertinence des récompenses, par défaut 0.9
    */
    DQNAgent(std::vector<int> net_shape, int nb_action, double lr = 0.01, double epsilon = 0.2, double gamma = 0.9);
    
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
     * @brief Méthode permettant d'entrainer l'agent et le réseau de neurone associé
     * @param state: std::vector<double>&, état courant de l'environnement
     * @param reward: double, récompense de l'agent, positive comme négative
     * @param next_state: std::vector<double>&, prochain état de l'environnement
     * @param done: done, permet de savoir si l'environnement est dans son état final ou non
    */
    void train(std::vector<double>& state, double reward, std::vector<double>& next_state, bool done);

  private:
    double learning_rate; // taux d'apprentissage du réseau de neurone
    double epsilon;       // taux facteur décisionnel de l'agent
    double gamma;         // taux de perinence des récompenses

    MLP *mlp;             // réseau de neurone multicouche associé à l'agent

    int action;           // dernière action de l'agent
    int nb_action;        // nombre d'action réalisable par l'agent
};
