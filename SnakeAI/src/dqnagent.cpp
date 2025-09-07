#include "headers/dqnagent.hpp"

DQNAgent::DQNAgent(std::vector<int> net_shape, int nb_action, double lr, double epsilon, double gamma)
{
  std::vector<int> temp;
  for (size_t i = 1; i < net_shape.size(); i++) temp.push_back(net_shape[i]);
  this->mlp = new MLP(temp, net_shape[0]);
  
  this->nb_action = nb_action;
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
