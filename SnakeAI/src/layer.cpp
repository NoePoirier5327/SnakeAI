#include "headers/layer.hpp"

Layer::Layer(int nb_neuron)
{
  this->nb_neuron = nb_neuron;

  // On créer les tableaux de pointeurs contenant les neurones, les sorties et les poids de chaque neurones
  //this->neurons = new Neuron [this->nb_neuron];
  //this->outputs = new double [this->nb_neuron];
  //this->weights = new double [this->nb_neuron];

  // On alloue la première case des tableaux de sorties et de poids à leurs taille
  //this->outputs[0] = this->nb_neuron + 1; this->weights[0] = this->nb_neuron + 1;
  
  // On instancie les neurones de la couche courante avec les sorties et les poids
  for (int i = 0; i < this->nb_neuron; i++)
  {
    //this->neurons[i] = Neuron();
    //this->outputs[i+1] = this->neurons[i].get_output(); // On incrémente l'index de 1 car à 0 il y a la taille du tableau
    //this->weights[i+1] = this->neurons[i].get_weight(); // pareille ici
    this->neurons.push_back(new Neuron());
    this->outputs.push_back(this->neurons[i]->get_output());
    this->weights.push_back(this->neurons[i]->get_weight());
  }
}

Layer::~Layer()
{
  for (int i = 0; i < this->nb_neuron; i++)
    delete this->neurons[i];
  /*
  // On détruit les tableaux des neurones, poids et sorties de la couche courante
  delete[] this->neurons;
  delete[] this->outputs;
  delete[] this->weights;
  */
}

std::vector<double> Layer::feed_forward(std::vector<double> inputs, std::vector<double> weights)
{
  // On fait prédire une sortie à chaque neurones et on stock leurs sorties dans le tableau
  for (int i = 0; i < this->nb_neuron; i++)
    this->outputs[i] = this->neurons[i]->feed_forward(inputs, weights);

  return this->outputs;
}

std::vector<double> Layer::backward_propagate(std::vector<double> deltas_next, std::vector<double> weights_next, double learning_rate, std::vector<double> prev_outputs)
{
  std::vector<double> deltas(this->nb_neuron, 0.0);
  for (int i = 0; i < this->nb_neuron; i++)
  {
    double delta = 0.0;
    for (int j = 0; j < (int)(deltas_next.size()); j++)
      delta += deltas_next[j] * weights_next[j];
    delta *= f_prime(this->neurons[i]->get_z());
    deltas[i] = delta;
    this->neurons[i]->update_parameters(delta, prev_outputs, learning_rate);
  }
  return deltas;
}

std::string Layer::display()
{
  std::string to_display = "";

  for (int i = 0; i < this->nb_neuron; i++)
    to_display += this->neurons[i]->display() + (i == this->nb_neuron-1 ? "" : " || ");
  to_display += "\n";

  return to_display;
}

std::vector<double> Layer::get_outputs() { return this->outputs; }
std::vector<double> Layer::get_weights() { return this->weights; }
int Layer::get_nb_neurons() { return this->nb_neuron; }

Neuron* Layer::get_neuron(int i)
{
  if (i >= 0 && i < this->nb_neuron) { return this->neurons[i]; }
  else { return nullptr; }
}
