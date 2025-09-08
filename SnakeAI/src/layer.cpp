#include "headers/layer.hpp"

Layer::Layer(int nb_neurons, int nb_inputs)
{
  this->nb_neurons = nb_neurons;
 
  // On instancie les neurones de la couche courante avec les sorties, les poids
  // et on récupère les valeurs avant activation de chaque neurones
  for (int i = 0; i < this->nb_neurons; i++)
    this->neurons.push_back(Neuron(nb_inputs));

  // On alloue la mémoire de la sortie et on la rempli de 0
  this->outputs.reserve(this->nb_neurons);
  for (int i = 0; i < this->nb_neurons; i++) this->outputs.push_back(0);
}

std::vector<double>& Layer::feed_forward(std::vector<double>& inputs)
{
  // On parcour les neurones et on prédit les sorties de la couche courante
  for (int i = 0; i < this->nb_neurons; i++)
    this->outputs[i] = this->neurons[i].feed_forward(inputs);

  return this->outputs;
}

std::string Layer::display()
{
  std::string to_display = "";

  for (int i = 0; i < this->nb_neurons; i++)
    to_display += this->neurons[i].display() + (i == this->nb_neurons-1 ? "" : " || ");
  to_display += "\n";

  return to_display;
}

Neuron& Layer::get_neuron(int index) { return this->neurons[index]; }
std::vector<double>& Layer::get_outputs() { return this->outputs; }
