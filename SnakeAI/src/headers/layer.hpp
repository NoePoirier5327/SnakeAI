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
    //~Layer();
    
    /**
     * @brief Méthode permettant à la couche de neurone de prédire une valeur
     * @param inputs:vector<double>, tableau contenant les entrées de la couche
     * @param weights:vector<double>, poid associée à chaque neurone
     * @return vector<double>, tableau contenant les prédictions de chaque neurones de la couche courante
    */
    std::vector<double> feed_forward(std::vector<double> inputs, std::vector<double> weights);
    
    /**
     * @brief Méthode permettant l'affichage du neurone courant
     * @return std::string, chaine de caractère à afficher
    */
    std::string display();
    
    /**
     * @brief Accesseur des sorties des neurones de la couche courante
     * @return vector<double>, tableau contenant la sortie de la couche de neurones
    */
    std::vector<double> get_outputs();
    
    /**
     * @brief Accesseur des poids des connections entre cette couche et la suivante
     * @return vector<double>, poids des connections entre cette couche et la suivante
    */
    std::vector<double> get_weights();
    
    /**
     * @brief Accesseur du nombre de neurones contenus dans la couche courante
     * @return int, nombre de neuron dans la couche courante
    */
    int get_nb_neurons();

  private:
    int nb_neuron; // nombre de neurone contenu dans la couche
    std::vector<Neuron> neurons; // tableau des neurones de la couche courante
    std::vector<double> outputs; // tableau contenant les sorties de la couche courante
    std::vector<double> weights; // tableau contenant les poids de la prochaine couche après celle là
};
