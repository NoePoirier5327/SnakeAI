#include "headers/layer.hpp"

Layer::Layer(int nb_neurons, int nb_inputs)
{
  this->nb_neurons = nb_neurons;
 
  // On instancie les neurones de la couche courante avec les sorties, les poids
  // et on récupère les valeurs avant activation de chaque neurones
  for (int i = 0; i < this->nb_neurons; i++)
    this->neurons.push_back(Neuron(nb_inputs));
}

/*
Layer::~Layer()
{
  for (int i = 0; i < this->nb_neuron; i++)
    delete this->neurons[i];
}
*/

std::vector<double> Layer::feed_forward(std::vector<double> inputs)
{
  std::vector<double> outputs;
  outputs.reserve(this->neurons.size());
  
  // On parcour les neurones et on prédit les sorties de la couche courante
  for (auto& neuron : this->neurons)
    outputs.push_back(neuron.feed_forward(inputs));

  return outputs;
}

std::string Layer::display()
{
  std::string to_display = "";

  for (int i = 0; i < this->nb_neurons; i++)
    to_display += this->neurons[i].display() + (i == this->nb_neurons-1 ? "" : " || ");
  to_display += "\n";

  return to_display;
}

int Layer::get_nb_neurons() { return this->nb_neurons; }
Neuron& Layer::get_neuron(int index) { return this->neurons[index]; }

std::vector<double> Layer::get_outputs()
{
  std::vector<double> outputs;
  outputs.reserve(this->neurons.size());

  for (auto& neuron: this->neurons)
    outputs.push_back(neuron.get_output());

  return outputs;  
}
