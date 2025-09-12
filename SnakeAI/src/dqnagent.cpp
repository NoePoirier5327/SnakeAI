#include "headers/dqnagent.hpp"

DQNAgent::DQNAgent(std::vector<int>& net_shape, double lr, double epsilon, double gamma)
{
  this->mlp = new MLP(net_shape);
  
  this->nb_action = net_shape.back();
  this->learning_rate = lr;
  this->epsilon = epsilon;
  this->gamma = gamma;
}

DQNAgent::~DQNAgent() { if (this->mlp == nullptr) delete this->mlp; }

int DQNAgent::decide(std::vector<double>& state)
{
  // L'agent explore
  if (rng(0.0, 1.0) < this->epsilon)
  {
    this->action = int_rng(0, this->nb_action-1); // on sauvegarde l'action de l'agent pour l'entrainement après
    return this->action;
  }

  // L'agent exploite son expérience
  std::vector<double> q_values = this->mlp->feed_forward(state);
  this->action = std::max_element(q_values.begin(), q_values.end()) - q_values.begin();
  return this->action;
}

void DQNAgent::train(std::vector<double>& state, double reward, std::vector<double>& next_state, bool done)
{
  std::vector<double> q_values = this->mlp->feed_forward(state);
  std::vector<double> next_q_values = this->mlp->feed_forward(next_state);
  
  double target = reward;
  if (done == false) // Si on est pas dans l'état final de l'agent, on calcule la pertinence de sa récompense
    target += this->gamma * (*std::max_element(next_q_values.begin(), next_q_values.end()));
  
  std::vector<double> target_vector = q_values;
  target_vector[this->action] = target;

  this->mlp->backward_propagate(target_vector, this->learning_rate);
}
