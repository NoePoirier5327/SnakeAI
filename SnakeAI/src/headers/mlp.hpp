#pragma once

#include "layer.hpp"
#include <vector>

/**
 * @brief Classe gérant le fonctionnement d'un réseau de neurones à plusieurs couches
*/
class MLP
{
  public:
    /**
     * @brief Constructeur du réseau de neurones à plusieurs couches
     * @param layers_shape: vector<int>&, contient, pour chaque couches, le nombre de neurones à instancier
    */
    MLP(std::vector<int>& layers_shape);
    
    /**
     * @brief Méthode permettant d'entrainer le réseau courant
     * @param inputs: std::vector<std::vector<double>>&, entrées pour lesquelles entrainer le réseau courant
     * @param targets: std::vector<std::vector<double>>&, sorties attendues du réseau
     * @param nb_iter: int, nombre d'itérations d'entrainement du réseau
     * @param learning_rate: double, taux d'apprentissage du réseau
    */
    void train(std::vector<std::vector<double>>& inputs, std::vector<std::vector<double>>& targets, int nb_iter, double learning_rate);
    
    /**
     * @brief Permet au réseau de prédire une valeur
     * @param inputs: vector<double>&, tableau contenant les entrées du réseau
     * @return vector<double>&, tableau correspondant à la sortie du réseau
    */
    std::vector<double>& feed_forward(std::vector<double>& inputs);
    
    /**
     * @brief Méthode permettant de faire apprendre le réseau tout entié
     * @param target: std::vector<double>, sortie voulu pour le réseau
     * @param learning_rate: double, taux d'apprentissage du réseau
     */
    void backward_propagate(std::vector<double>& target, double learning_rate);
    
    /**
     * @brief Méthode renvoyant une chaine à afficher correspondant à la représentation du réseau
     * @return std::string, chaine de caractère représentant le réseau de neurones
    */
    std::string display();
    
    /**
     * @brief Accesseur des sorties du réseau
     * @return vector<double>, tableau contenant les sorties du réseau, index 0 -> taille du tableau
    */
    std::vector<double>& get_outputs();

    private:
      std::vector<Layer> layers; // Tableau contenant les instances de chaque couche de neurones
      std::vector<double> outputs; // tableau contenant les sorties du réseau
      std::vector<double> old_input; // On sauvegarde les entrées du réseau pour les affichers plus tard
};
