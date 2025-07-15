#pragma once

#include "layer.hpp"

/**
 * @brief Classe gérant le fonctionnement d'un réseau de neurones à plusieurs couches
*/
class MLP
{
  public:
    /**
     * @brief Constructeur du réseau de neurones à plusieurs couches
     * @param nb_neurons:int*, contient, pour chaque couches, le nombre de neurones à instancier, à l'index 0, il y a la taille du tableau
     * @param nb_inputs:int, nombre d'entrées pour le réseau de neurones
    */
    MLP(int* nb_neurons, int nb_inputs);
    
    /**
     * @brief Destructeur du réseau de neurones à plusieurs couches
    */
    ~MLP();
    
    /**
     * @brief Permet au réseau de prédire une valeur
     * @param inputs:double*, tableau contenant les entrées du réseau, à l'index 0, il y a la taille du tableau
     * @return double*, tableau correspondant à la sortie du réseau, index 0 -> taille du tableau
    */
    double* feed_forward(double* inputs);
    
    /**
     * @brief Méthode renvoyant une chaine à afficher correspondant à la représentation du réseau
     * @return std::string, chaine de caractère représentant le réseau de neurones
    */
    std::string display();
    
    /**
     * @brief Accesseur des sorties du réseau
     * @return double*, tableau contenant les sorties du réseau, index 0 -> taille du tableau
    */
    double* get_outputs();

    private:
      Layer **layers; // Tableau contenant les instances de chaque couche de neurones
      int nb_layers; // nombre de couches instanciées dans le réseau
      int nb_inputs; // nombre d'entrées de la première couche
      double* outputs; // tableau contenant les sorties du réseau
      double* input_weights; // tableau contenant les poids de la couche d'entrée du réseau
};
