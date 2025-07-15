#include "headers/mlp.hpp"

MLP::MLP(int *nb_neurons, int nb_inputs)
{
  this->nb_layers = nb_neurons[0] - 1;
  this->nb_inputs = nb_inputs;
  
  // On alloue la mémoire pour le réseau à plusieurs couches et la sortie
  this->layers = new Layer* [this->nb_layers];
  this->outputs = new double [this->nb_layers+1]; // Parce que à l'index 0 il y a la taille du tableau
  this->input_weights = new double[nb_inputs+1]; // pareille ici

  // On instancie les couches
  for (int i = 0; i < this->nb_layers; i++)
    this->layers[i] = new Layer(nb_neurons[i+1]);

  // On construit le tableau contenant les sorties
  this->outputs[0] = this->layers[this->nb_layers-1]->get_outputs()[0];

  for (int i = 1; i < this->outputs[0]; i++)
    this->outputs[i] = this->layers[this->nb_layers]->get_outputs()[i];

  // On construit celui conenant les poids des entrées, on l'initialise à des poids aléatoires
  this->input_weights[0] = nb_inputs +1;

  for (int i = 1; i <= nb_inputs; i++)
    this->input_weights[i] = rng(-1.0, 1.0);
}

MLP::~MLP()
{
  // On dé instancie les couches
  for (int i = 0; i < this->nb_layers; i++)
    delete this->layers[i];

  // On dé alloue la mémoire pour les couches et les sorties
  delete[] this->layers;
  delete[] this->outputs;
}

double* MLP::feed_forward(double *inputs)
{
  // On parcours le réseau 
  double* temp_weight = new double [this->nb_inputs];
  for (int i = 0; i < this->nb_layers; i++)
  {
    
  }

  // On copie la sortie du réseau dans le tableau de sortie
  int array_size = this->layers[this->nb_layers]->get_outputs()[0];
  for (int i = 1; i < array_size; i++)
    this->outputs[1] = this->layers[this->nb_layers]->get_outputs()[i];
  return this->outputs;
}
