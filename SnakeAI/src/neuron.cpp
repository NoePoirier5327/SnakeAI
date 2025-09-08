#include "headers/neuron.hpp"

Neuron::Neuron(int nb_inputs)
{
  this->output = 0.0;
  this->bias = rng(-1.0, 1.0);

  // On initialise les poids du neurone
  for (int i = 0; i < nb_inputs; i++)
    this->weights.push_back(rng(-1.0, 1.0));
}

double Neuron::feed_forward(std::vector<double>& inputs)
{
  int n = inputs.size(); // On a défini la taille du tableau à la première case du tableau, les tableaux de poids et d'entrées ont la même taille
  this->output = this->bias;
  
  // On parcour les tableaux d'entrées et de poids pour calculé la sortie du neurone courant
  // la sortie du neurone courant est la somme de la multiplication des entrées par les poids + le biais courant passée dans une fonction d'activation
  for (int i = 0; i < n; i++)
    this->output += inputs[i] * this->weights[i];
  this->output = f(this->output);

  return this->output; // On renvoie la prédiction du neurone
}

void Neuron::update_weights(std::vector<double>& inputs, double delta, double learning_rate)
{
  for (int i = 0; i < (int)(this->weights.size()); i++)  
    this->weights[i] += learning_rate * delta * inputs[i];
  this->bias += learning_rate * delta;
}

std::string Neuron::display()
{ 
  std::string to_display = "";
  to_display += std::to_string(this->output);
  //to_display += " | Bias : " + std::to_string(this->bias);
  //to_display += " | Weight : " + std::to_string(this->weight);
  return to_display; 
}

// Accesseurs de l'objet courant
std::vector<double>& Neuron::get_weights() { return this->weights; }
double Neuron::get_output() { return this->output; }
