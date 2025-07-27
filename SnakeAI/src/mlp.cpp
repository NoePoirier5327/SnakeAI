#include "headers/mlp.hpp"

MLP::MLP(std::vector<int> nb_neurons, int nb_inputs)
{
  //this->nb_layers = nb_neurons[0] - 1;
  this->nb_layers = nb_neurons.size();
  this->nb_inputs = nb_inputs;
  
  // On alloue la mémoire pour le réseau à plusieurs couches et la sortie
  //this->layers = new Layer* [this->nb_layers];
  //this->outputs = new double [this->nb_layers+1]; // Parce que à l'index 0 il y a la taille du tableau
  //this->input_weights = new double[nb_inputs+1]; // pareille ici

  // On instancie les couches
  for (int i = 0; i < this->nb_layers; i++)
    this->layers.push_back(new Layer(nb_neurons[i]));
    //this->layers[i] = new Layer(nb_neurons[i+1]);

  // On construit le tableau contenant les sorties en récupèrant les dernières sorties du percéptron
  //this->outputs[0] = this->layers[this->nb_layers-1]->get_outputs()[0];
  int size_outputs = this->layers[this->nb_layers-1]->get_outputs()[0];

  for (int i = 0; i < size_outputs; i++)
    this->outputs.push_back(this->layers[this->nb_layers-1]->get_outputs()[i]);

  // On construit celui conenant les poids des entrées, on l'initialise à des poids aléatoires
  for (int i = 0; i < nb_inputs; i++)
    this->input_weights.push_back(rng(-1.0, 1.0));
}

MLP::~MLP()
{
  // On désinstancie les couches
  for (int i = 0; i < this->nb_layers; i++)
    delete this->layers[i];

  // On désalloue la mémoire pour les couches et les sorties
  //delete[] this->layers;
  //delete[] this->outputs;
}

std::vector<double> MLP::feed_forward(std::vector<double> inputs)
{
  // On parcours le réseau 
  std::vector<double> temp_weight;
  for (int i = 0; i < this->nb_layers; i++)
  {
    
  }

  // On copie la sortie du réseau dans le tableau de sortie
  int array_size = this->layers[this->nb_layers]->get_outputs()[0];
  for (int i = 1; i < array_size; i++)
    this->outputs[1] = this->layers[this->nb_layers]->get_outputs()[i];
  return this->outputs;
}

std::string MLP::display()
{
  std::string to_disp;
  for (int i = 0; i < this->nb_layers; i++)
    to_disp += this->layers[i]->display() + "\n";
  return to_disp;
}

std::vector<double> MLP::get_outputs() { return this->outputs; }
