#pragma once

#include "neuron.hpp"

/**
 * @brief Classe gérant le fonctionnement d'une couche de neurone du réseaux à plusieurs couche
*/
class Layer
{
  public:
    /**
     * @brief Constructeur de la couche courante
     * @param nb_neurone:int, nombre de neurone contenu dans la couche courante
    */
    Layer(int nb_neurone);
    
    /**
     * @brief Destructeur de la couche courante, désinstancie le tabelau de neurone et de sortie de la couche courante
    */
    ~Layer();
    
    /**
     * @brief Méthode permettant à la couche de neurone de prédire une valeur
     * @param inputs:double*, tableau contenant les entrées de la couche
     * @param weights:double*, poid associée à chaque neurone
     * @return double*, tableau contenant les prédictions de chaque neurones de la couche courante
    */
    double* feed_forward(double *inputs, double *weights);
    
    /**
     * @brief Méthode permettant l'affichage du neurone courant
     * @return std::string, chaine de caractère à afficher
    */
    std::string display();
    
    /**
     * @brief Accesseur des sorties des neurones de la couche courante
     * @return double*, tableau contenant la sortie de la couche de neurones
    */
    double* get_outputs();
    
    /**
     * @brief Accesseur des poids des connections entre cette couche et la suivante
     * @return double*, poids des connections entre cette couche et la suivante
    */
    double* get_weights();
    
    /**
     * @brief Accesseur du nombre de neurones contenus dans la couche courante
     * @return int, nombre de neuron dans la couche courante
    */
    int get_nb_neurons();

  private:
    int nb_neuron; // nombre de neurone contenu dans la couche
    Neuron *neurons; // tableau des neurones de la couche courante
    double *outputs; // tableau contenant les sorties de la couche courante
    double *weights; // tableau contenant les poids de la prochaine couche après celle là
};
