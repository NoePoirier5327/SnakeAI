#include "headers/layer.hpp"

Layer::Layer(int nb_neuron)
{
  this->nb_neuron = nb_neuron;

  // On créer les tableaux de pointeurs contenant les neurones, les sorties et les poids de chaque neurones
  this->neurons = new Neuron [this->nb_neuron];
  this->outputs = new double [this->nb_neuron+1]; // On ajoute 1 car la première case du tableau contient toujour sa taille
  this->weights = new double [this->nb_neuron+1]; // pareille ici

  // On alloue la première case des tableaux de sorties et de poids à leurs taille
  this->outputs[0] = this->nb_neuron + 1; this->weights[0] = this->nb_neuron + 1;
  
  // On instancie les neurones de la couche courante avec les sorties et les poids
  for (int i = 0; i < this->nb_neuron; i++)
  {
    this->neurons[i] = Neuron();
    this->outputs[i+1] = this->neurons[i].get_output(); // On incrémente l'index de 1 car à 0 il y a la taille du tableau
    this->weights[i+1] = this->neurons[i].get_weight(); // pareille ici
  }
}

Layer::~Layer()
{
  // On détruit les tableaux des neurones, poids et sorties de la couche courante
  delete[] this->neurons;
  delete[] this->outputs;
  delete[] this->weights;
}

double* Layer::feed_forward(double *inputs, double *weights)
{
  // On fait prédire une sortie à chaque neurones et on stock leurs sorties dans le tableau
  for (int i = 0; i < this->nb_neuron; i++)
    this->outputs[i+1] = this->neurons[i].feed_forward(inputs, weights);

  return this->outputs;
}

std::string Layer::display()
{
  std::string to_display = "";

  for (int i = 0; i < this->nb_neuron; i++)
    to_display += this->neurons[i].display() + (i == this->nb_neuron-1 ? "" : " // ");
  to_display += "\n";

  return to_display;
}

double* Layer::get_outputs() { return this->outputs; }
double* Layer::get_weights() { return this->weights; }
int Layer::get_nb_neurons() { return this->nb_neuron; }
