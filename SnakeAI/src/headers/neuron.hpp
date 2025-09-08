#pragma once

#include "global.hpp"
#include <string>
#include <cmath>
#include <vector>

/**
 * @brief Classe gérant le fonctionnement d'un neurone du réseau
*/
class Neuron
{
  public:
    /**
     * @brief Constructeur du neurone courant, initialise le biais et le poid du neurone à une valeur aléatoire
     * @param nb_inputs: int, nombre d'entrées du neurone pour initialiser les poids correspondant aux connections
    */
    Neuron(int nb_inputs);
    
    /**
     * @brief Méthode permettant au neurone de prédire une valeur
     * @param inputs: std::vector<double>&, vecteur contenant les entrées du réseau
     * @return double, sortie du neurone courant
    */
    double feed_forward(std::vector<double>& inputs);
    
    /**
     * @brief Méthode d'affichage du neurone courant
     * @return std::string, chaine de caractère à afficher
    */
    std::string display();
    
    /**
     * @brief Mutateur du poid courant, corrige le poid pour la back propagation
     * @param inputs: std::vector<double>&, entrées correct du neurone
     * @param delta: double,
     * @param learning_rate: double, taux d'apprentissage du neurone
    */
    void update_weights(std::vector<double>& inputs, double delta, double learning_rate);
    
    /**
     * @brief Accesseur des poids du neurone
     * @param std::vector<double>&, poids du neurone courant
    */
    std::vector<double>& get_weights();
    
    /**
     * @brief Accesseur de la sortie du neuron courant
     * @return double, sortie du neurone courante
    */
    double get_output();

  private:
    double bias; // biais du neurone
    std::vector<double> weights; // poids du neurone courant
    double output; // sortie du neurone après activation
};
