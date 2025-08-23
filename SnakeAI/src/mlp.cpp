#include "headers/mlp.hpp"
#include <string>

MLP::MLP(std::vector<int> nb_neurons, int nb_inputs)
{
  // Par défaut les entrées du réseau sont à -1
  this->old_input = {-1};

  //this->nb_layers = nb_neurons[0] - 1;
  this->nb_layers = nb_neurons.size();
  //this->nb_inputs = nb_inputs;
  
  // On alloue la mémoire pour le réseau à plusieurs couches et la sortie
  //this->layers = new Layer* [this->nb_layers];
  //this->outputs = new double [this->nb_layers+1]; // Parce que à l'index 0 il y a la taille du tableau
  //this->input_weights = new double[nb_inputs+1]; // pareille ici

  // On instancie les couches
  for (int i = 0; i < this->nb_layers; i++)
    this->layers.push_back(new Layer(nb_neurons[i]));
    //this->layers[i] = new Layer(nb_neurons[i+1]);

  // On construit le tableau contenant les sorties en récupèrant les dernières sorties du percéptron
  this->outputs = this->layers[this->nb_layers - 1]->get_outputs();
  //this->outputs[0] = this->layers[this->nb_layers-1]->get_outputs()[0];
  //int size_outputs = this->layers[this->nb_layers-1]->get_outputs()[0];

  //for (int i = 0; i < size_outputs; i++)
    //this->outputs.push_back(this->layers[this->nb_layers-1]->get_outputs()[i]);

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
  old_input = inputs; // On sauvegarde les entrées pour pouvoir les affichers

  // On parcours le réseau 
  // Tout d'abord, on parcours la couche d'entrée
  std::vector<double> temp_weight;
  std::vector<double> temp_input;

  this->layers[0]->feed_forward(inputs, this->input_weights);
  temp_input = this->layers[0]->get_outputs();
  temp_weight = this->layers[0]->get_weights();

  // Ensuite, on parcours le reste du réseau
  for (int i = 1; i < this->nb_layers; i++)
  {
    this->layers[i]->feed_forward(temp_input, temp_weight); // On prédit en passant la sortie et les poids précédents en paramètres
    temp_input = this->layers[i]->get_outputs(); // On récupère la sortie comme nouvelle entrée
    temp_weight = this->layers[i]->get_weights(); // On récupère les poids de cette couche comme nouveaux poids
  }

  // On copie la sortie du réseau dans le tableau de sortie et on le renvoie
  this->outputs = temp_input;
  return this->outputs;
}

void MLP::backward_propagate(std::vector<double> target, double learning_rate)
{

}

std::string MLP::display()
{
  std::string to_disp;

  // d'abord, on afficher les entrées qui font partis d'une couche à part
  to_disp = "Input layer :\n";
  int size = this->old_input.size();
  for (int i = 0; i < size; i++)
    to_disp += std::to_string(this->old_input[i]) + (i == size - 1 ? "" : " || ");
  to_disp += "\n\n";

  to_disp += "Hidden layer :\n";
  for (int i = 0; i < this->nb_layers-1; i++)
    to_disp += this->layers[i]->display();

  to_disp += "\nOutput layer:\n" + this->layers[this->nb_layers-1]->display();

  return to_disp;
}

std::vector<double> MLP::get_outputs() { return this->outputs; }
