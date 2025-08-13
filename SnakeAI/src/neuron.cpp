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
  this->z = 0.0;
}

double Neuron::feed_forward(std::vector<double> inputs, std::vector<double> weights)
{
  int n = inputs.size(); // On a défini la taille du tableau à la première case du tableau, les tableaux de poids et d'entrées ont la même taille
  this->z = 0.0; // On remet la valeur précédente à 0 pour éviter les problèmes de prédiction
  
  // On parcour les tableaux d'entrées et de poids pour calculé la sortie du neurone courant
  // la sortie du neurone courant est la somme de la multiplication des entrées par les poids + le biais courant passée dans une fonction d'activation
  for (int i = 0; i < n; i++)
    this->z += inputs[i] * weights[i];
  this->z += this->bias; // on ajoute le biais du neurone
  this->output = f(this->z); // on active le neurone courant

  return this->output; // On renvoie la prédiction du neurone
}

double Neuron::compute_delta(double delta_next, double weight_next, double learning_rate) { return delta_next * weight_next * f_prime(this->z); }

void Neuron::update_parameters(double delta, std::vector<double> prev_outputs, double learning_rate)
{
  // Mise à jour du biais
  this->bias -= learning_rate * delta;
  // Mise à jour du poids (ici, on suppose que prev_outputs est la sortie du neurone précédent)
  // En pratique, dans une couche, il faut boucler sur tous les neurones précédents
  // Ici, on simplifie pour l'exemple
  this->weight -= learning_rate * delta * prev_outputs[0];
}

std::string Neuron::display()
{ 
  std::string to_display = "";
  to_display += std::to_string(this->output);
  //to_display += " | Bias : " + std::to_string(this->bias);
  //to_display += " | Weight : " + std::to_string(this->weight);
  return to_display; 
}

// Fonctions d'activation
double f(double x) { return (1/(1 + exp(-1 * x))); }
double f_prime(double x) { return exp(-1 * x) / pow(1 + exp(-1 * x) , 2); }

// Accesseurs de l'objet courant
double Neuron::get_output() { return this->output; }
double Neuron::get_bias() { return this->bias; }
double Neuron::get_weight() { return this->weight; }
double Neuron::get_z() { return this->z; }

// Mutateurs de l'objet courant
void Neuron::set_bias(double bias) { this->bias = bias; }
void Neuron::set_weight(double weight) { this->weight = weight; }
