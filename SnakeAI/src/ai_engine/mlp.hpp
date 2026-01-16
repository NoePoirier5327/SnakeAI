#pragma once

/**
 * Fichier contenant la déclaration d'une réseau de neurone artificiel multicouche générique
 * en 2025
 * par Noé Poirier
*/

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
    MLP(const std::vector<int>& layers_shape);
    
    /**
     * @brief Méthode permettant d'entrainer le réseau courant
     * @param inputs: std::vector<std::vector<double>>&, entrées pour lesquelles entrainer le réseau courant
     * @param targets: std::vector<std::vector<double>>&, sorties attendues du réseau
     * @param nb_iter: int, nombre d'itérations d'entrainement du réseau
     * @param learning_rate: float, taux d'apprentissage du réseau
    */
    void train(std::vector<std::vector<double>>& inputs, std::vector<std::vector<double>>& targets, int nb_iter, float learning_rate);
    
    /**
     * @brief Permet au réseau de prédire une valeur
     * @param inputs: vector<double>&, tableau contenant les entrées du réseau
     * @return vector<float>&, tableau correspondant à la sortie du réseau
    */
    std::vector<double>& feed_forward(std::vector<double>& inputs);
    
    /**
     * @brief Méthode permettant de faire apprendre le réseau tout entié
     * @param target: std::vector<double>, sortie voulu pour le réseau
     * @param learning_rate: float, taux d'apprentissage du réseau
     */
    void backward_propagate(std::vector<double>& target, float learning_rate);
    
    /**
     * @brief Méthode permettant de copier le contenu du MLP en paramètre dans celui courant
     * @param mlp: MLP, mlp à copier dans le mlp courant
    */
    void copy(MLP& mlp);
    
    /**
     * @brief Accesseur de la forme globale du mlp courant
     * @return std::vector<int>, forme globale du mlp courant
    */
    std::vector<int>& get_net_shape();
    
    /**
     * @brief Accesseur d'une couche i du réseau
     * @param i: size_t, couche à laquelle on veut accéder
     * @param layer: Layer, modifier par la méthode, correspond à la couche qu'on voulait, n'est pas modifier si erreur
     * @return bool, true si aucun problème, false si i est en dehors de l'ensemble de définition des couches du réseau
    */
    bool get_layer(size_t &i, Layer &layer);
    
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
      
      std::vector<int> net_shape; // Forme globale du réseau
};
