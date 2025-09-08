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
     * @param nb_neurons: int, nombre de neurone contenu dans la couche courante
     * @param nb_inputs: int, nombre d'entrées de la couche de neurone
    */
    Layer(int nb_neurons, int nb_inputs);
    
    /**
     * @brief Méthode permettant à la couche de neurone de prédire une valeur
     * @param inputs:vector<double>&, tableau contenant les entrées de la couche
     * @return vector<double>&, tableau contenant les prédictions de chaque neurones de la couche courante
    */
    std::vector<double>& feed_forward(std::vector<double>& inputs);
    
    /**
     * @brief Méthode permettant l'affichage du neurone courant
     * @return std::string, chaine de caractère à afficher
    */
    std::string display();
    
    /**
     * @brief Accesseur des sorties des neurones de la couche courante
     * @return vector<double>&, tableau contenant la sortie de la couche de neurones
    */
    std::vector<double>& get_outputs();
    
    /**
     * @brief Accesseur des neurones de la couche courante
     * @param index: int, index du neurone dans la couche
     * @return Neuron&, pointeur vers le neurone courant
    */
    Neuron& get_neuron(int index);

  private:
    int nb_neurons; // nombre de neurone contenu dans la couche
    std::vector<Neuron> neurons; // tableau des neurones de la couche courante
    std::vector<double> outputs;
};
