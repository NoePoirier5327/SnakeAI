#include "headers/neuron.hpp"

double rng(double min, double max)
{
  // Création d'un moteur aléatoire static (il n'est appelée qu'une seule fois durant la compilation)
  static std::random_device rd;
  static std::mt19937 gen(rd());

  // création d'une distribution uniforme réelle
  std::uniform_real_distribution<double> dis(min, max);

  // On renvoie le nombre généré aléatoirement
  return dis(gen);
}

Neuron::Neuron()
{
  this->output = rng(-1.0, 1.0);
  this->bias = rng(-1.0, 1.0);
  this->weight = rng(-1.0, 1.0);
}

double Neuron::feed_forward(double *inputs, double *weights)
{
  int n = inputs[0]; // On a défini la taille du tableau à la première case du tableau, les tableaux de poids et d'entrées ont la même taille
  
  // On parcour les tableaux d'entrées et de poids pour calculé la sortie du neurone courant
  // la sortie du neurone courant est la somme de la multiplication des entrées par les poids + le biais courant passée dans une fonction d'activation
  for (int i = 1; i < n; i++)
    this->output += inputs[i] * weights[i];
  this->output += this->bias; // on ajoute le biais du neurone
  this->output = this->f(this->output); // on active le neurone courant

  return this->output; // On renvoie la prédiction du neurone
}

std::string Neuron::display()
{ 
  std::string to_display = "";
  to_display += "Output : " + std::to_string(this->output);
  to_display += " | Bias : " + std::to_string(this->bias);
  to_display += " | Weight : " + std::to_string(this->weight);
  return to_display; 
}

// Fonctions d'activation
double Neuron::f(double x) { return (1/(1 + exp(-1 * x))); }
double Neuron::f_prime(double x) { return exp(-1 * x) / pow(1 + exp(-1 * x) , 2); }

// Accesseurs de l'objet courant
double Neuron::get_output() { return this->output; }
double Neuron::get_bias() { return this->bias; }
double Neuron::get_weight() { return this->weight; }

// Mutateurs de l'objet courant
void Neuron::set_bias(double bias) { this->bias = bias; }
void Neuron::set_weight(double weight) { this->weight = weight; }
