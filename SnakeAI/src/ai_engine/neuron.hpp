#pragma once

/**
 * Fichier contenant la déclaration du fonctionnement générale d'un neurone artificiel
 * en 2025
 * par Noé Poirier
*/

#include <string>
#include <cmath>
#include <vector>
#include <random>

/**
 * @brief Fonction d'acitvation des neurones
 * @param x: double, valeur à activer
 * @return double, valeur activée
*/
double f(double x);

/**
 * @brief Dérivée de la fonction d'activation des neurone (utilisé pour l'apprentissage en règle général)
 * @param x: double, valeur à activer
 * @return double, valeur activée
*/
double f_prime(double x);

/**
 * @brief Fonction permettant la génération d'un nombre aléatoire entre deux bornes
 * @param min:double, borne minimale pour la génération aléatoire
 * @param max:double, borne maximale pour la génération aléatoire
 * @return double, nombre aléatoire généré par la fonction
*/
double rng(double min, double max);

/**
 * @brief Fonction générant un nombre aléatoire entier entre deux bornes entières
 * @param min: int, borne minimale
 * @param max: int, borne maximale
 * @return int, nombre aléatoire généré par la fonction
*/
int int_rng(int min, int max);


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
