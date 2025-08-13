#pragma once

#include <string>
#include <random>
#include <cmath>
#include <vector>

/**
 * @brief Fonction permettant la génération d'un nombre aléatoire entre deux bornes
 * @param min:double, borne minimale pour la génération aléatoire
 * @param max:double, borne maximale pour la génération aléatoire
 * @return double, nombre aléatoire généré par la fonction
*/
double rng(double min, double max);

/**
 * @brief Fonction d'acitvation des neurones
 * @param x: double, valeur à activer
 * @return double, valeur activée
*/
double f(double x);

/**
 * @brief dérivée de la fonction d'activation des neurone (utilisé pour l'apprentissage en règle général)
 * @param x: double, valeur à activer
 * @return double, valeur activée
*/
double f_prime(double x);

/**
 * @brief Classe gérant le fonctionnement d'un neurone du réseau
*/
class Neuron
{
  public:
    /**
     * @brief Constructeur du neurone courant, initialise le biais et le poid du neurone à une valeur aléatoire
    */
    Neuron();
    
    /**
     * @brief Méthode permettant au neurone de prédire une valeur
     * @param inputs: std::vector<double>, vecteur contenant les entrées du réseau
     * @param weights: std::vector<double>, vecteur contenant les poids associées aux neurones de la couche supérieur
     * @return double, sortie du neurone courant
    */
    double feed_forward(std::vector<double> inputs, std::vector<double> weights);
    
    /**
     * @brief Méthode permettant de calculer le gradient local
     * @param delta_next: double, prochain gradient local du réseau
     * @param weight_next: double, prochain poid du réseau
     * @param learning_rate: double, taux d'apprentissage
     * @return double, gradient local
    */
    double compute_delta(double delta_next, double weight_next, double learning_rate);
    
    /**
     * @brief Méthode permettant de mettre à jour les paramètres du neurone courant
     * @param delta: double, gradient local
     * @param prev_outputs: std::vector<double>, vecteur standard contenant les sorties précédentes
     * @param learning_rate: double, taux d'apprentissage du neurone
    */
    void update_parameters(double delta, std::vector<double> prev_outputs, double learning_rate);
    
    /**
     * @brief Accesseur de la valeur du neurone avant activation
     * @return double, valeur du neurone avant activation
    */
    double get_z();
    
    /**
     * @brief Méthode d'affichage du neurone courant
     * @return std::string, chaine de caractère à afficher
    */
    std::string display();
    
    /**
     * @brief Accesseur de la sortie du neurone
     * @return double, sortie du neurone
    */
    double get_output();
    
    /**
     * @brief Mutateur du poid entre ce neurone et ceux de la prochaine couche
     * @param weight:double, poid du neurone courant
    */
    void set_weight(double weight);
    
    /**
     * @brief Accesseur du poid du neurone courant
     * @return double, poid du neurone
    */
    double get_weight();
    
    /**
     * @brief Mutateur du biais du neurone courant
     * @param bias:double, biais du neurone courant
    */
    void set_bias(double bias);
    
    /**
     * @brief Accesseur du biais du neurone courant
     * @return double, biais du neurone courant
    */
    double get_bias();

  private:
    double bias; // biais du neurone
    double weight; // poid de la connexion entre le neurone courant et les neurones de la prochaine couche
    double output; // sortie du neurone
    double z; // valeur du neurone avant activation
};
