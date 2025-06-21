#pragma once

#include <string>
#include <random>
#include <cmath>

/**
 * @brief Fonction permettant la génération d'un nombre aléatoire entre deux bornes
 * @param min:double, borne minimale pour la génération aléatoire
 * @param max:double, borne maximale pour la génération aléatoire
 * @return double, nombre aléatoire généré par la fonction
*/
double rng(double min, double max);

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
     * @param inputs: double *, vecteur contenant les entrées du réseau
     * @param weights: double *, vecteur contenant les poids associées aux neurones de la couche supérieur
     * @return double, sortie du neurone courant
    */
    double feed_forward(double *inputs, double *weights);
    
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
    /**
     * @brief Fonction d'activation du neurone
     * @param x:double, entrée de la fonction
     * @return double, image de la fonction
    */
    double f(double x);
    
    /**
     * @brief Dérivée de la fonction d'activation du réseau de neurone
     * @param x:double, entrée de la fonction
     * @return double, image de la fonction dérivée
    */
    double f_prime(double x);

    double bias; // biais du neurone
    double weight; // poid de la connexion entre le neurone courant et les neurones de la prochaine couche
    double output; // sortie du neurone
};
