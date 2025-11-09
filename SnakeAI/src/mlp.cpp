#include "headers/mlp.hpp"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>

MLP::MLP(std::vector<int>& layers_shape)
{
  // Par défaut les entrées du réseau sont à -1
  this->old_input = {-1};

  //this->nb_layers = nb_neurons[0] - 1;
  int nb_layers = layers_shape.size();
  int inputs_size = layers_shape[0];

  // On instancie les couches et on récupère les valeurs avant activation de leurs neurones
  for (int i = 1; i < nb_layers; i++)
  {
    this->layers.push_back(Layer(layers_shape[i], inputs_size));
    inputs_size = layers_shape[i];
  }

  // On alloue la mémoire nécessaire à la taille de la sortie du réseau
  this->outputs.reserve(layers_shape.back());
}

void MLP::train(std::vector<std::vector<double>>& inputs,
                std::vector<std::vector<double>>& targets,
                int nb_iter,
                float learning_rate)
{
  std::cout << "Entrainement du réseau sur "<< nb_iter <<" d'itérations." << std::endl;
  
  time_t start = time(nullptr);

  int i = 0; int n = inputs.size();
  for (int _ = 0; _ < nb_iter; _++)
  {
    if (i == n) i = 0;
    
    this->feed_forward(inputs[i]);
    this->backward_propagate(targets[i], learning_rate);

    i++;
  }
  
  time_t finish = time(nullptr);

  std::cout << "Entrainement fini." << std::endl;
  std::cout << "Temps d'exécution : " << (finish - start) << " secondes." << std::endl;
}

std::vector<double>& MLP::feed_forward(std::vector<double>& inputs)
{
  this->old_input = inputs; // On sauvegarde les entrées pour pouvoir les affichers
  this->outputs = inputs;

  for (auto& layer: this->layers)
    this->outputs = layer.feed_forward(this->outputs);

  return this->outputs;
}

void MLP::backward_propagate(std::vector<double>& target, float learning_rate) 
{
  std::vector<std::vector<double>> deltas(this->layers.size());

  // Dernière couche
  Layer& output_layer = this->layers.back();
  deltas.back().resize(output_layer.get_outputs().size());

  for (size_t i = 0; i < output_layer.get_outputs().size(); i++)
  {
    double output = output_layer.get_outputs()[i];
    deltas.back()[i] = (target[i] - output) * (output * (1 - output));
  }

  // Couches cachées
  for (int l = this->layers.size() - 2; l >= 0; l--)
  {
    Layer& current_layer = this->layers[l];
    Layer& next_layer = this->layers[l + 1];
    deltas[l].resize(current_layer.get_outputs().size());

    for (size_t i = 0; i < current_layer.get_outputs().size(); i++)
    {
      double sum = 0.0;
      for (size_t j = 0; j < next_layer.get_outputs().size(); j++)
        sum += next_layer.get_neuron(j).get_weights()[i] * deltas[l + 1][j];
      double output = current_layer.get_outputs()[i];
      deltas[l][i] = sum * (output * (1 - output));
    }
  }

  // Mise à jour des poids
  for (size_t l = 0; l < this->layers.size(); l++)
  {
    std::vector<double> inputs = (l == 0) ? this->old_input : this->layers[l - 1].get_outputs();
    for (size_t j = 0; j < this->layers[l].get_outputs().size(); j++)
      this->layers[l].get_neuron(j).update_weights(inputs, deltas[l][j], learning_rate);
  }
}

std::string MLP::display()
{
  std::string to_disp;

  // d'abord, on affiche les entrées qui font partis d'une couche à part
  to_disp = "Input layer :\n";
  int size = this->old_input.size();
  for (int i = 0; i < size; i++)
    to_disp += std::to_string(this->old_input[i]) + (i == size - 1 ? "" : " || ");
  to_disp += "\n\n";

  // Ensuite les couches cachées
  to_disp += "Hidden layer :\n";
  for (size_t i = 0; i < this->layers.size()-1; i++)
    to_disp += this->layers[i].display();

  // Enfin 
  to_disp += "\nOutput layer:\n" + this->layers.back().display();

  return to_disp;
}

std::vector<double>& MLP::get_outputs() { return this->outputs; }
