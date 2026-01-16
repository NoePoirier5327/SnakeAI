/**
 * Fichier contenant l'implémentation d'un agent d'apprentissage profond
 * en 2025
 * par Noé Poirier
*/

#include "dqnagent.hpp"

DQNAgent::DQNAgent(const std::vector<int>& net_shape, const float &lr, const float &epsilon, const float &gamma, const int &batch_size, const int &max_memory_size, const float &epsilon_decay, const float &epsilon_end, const int &convergence_counter)
{
  this->mlp = new MLP(net_shape);
  this->target_network = new MLP(net_shape);
  
  this->nb_action = net_shape.back();
  this->learning_rate = lr;
  this->epsilon = epsilon;
  this->gamma = gamma;

  this->iteration = 1;

  this->memory = new std::vector<Episodes>;
  this->batch_size = batch_size;
  this->max_memory_size = max_memory_size;

  this->epsilon_decay = epsilon_decay;
  this->epsilon_end = epsilon_end;
  this->convergence_counter = convergence_counter;
}

DQNAgent::~DQNAgent()
{ 
  if (this->mlp != nullptr) delete this->mlp; 
  if (this->target_network != nullptr) delete this->target_network;
  delete this->memory;
}

int DQNAgent::decide(std::vector<double>& state)
{
  // On modifie epsilon au fur et à mesure du temps toute les 100 itérations pour éviter qu'il converge trop vite
  if (this->iteration % this->convergence_counter == 0)
    this->epsilon = std::max(this->epsilon_end, static_cast<float>(this->epsilon - pow(10, -5)));

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

void DQNAgent::train_short_term(std::vector<double>& state, float reward, std::vector<double>& next_state, bool done, bool store_memory)
{
  if (store_memory)
  {
    // Si on dépasse la mémoire autorisée pour la mémoire de l'agent, on supprime son premier élément
    if (this->memory->size() >= this->max_memory_size) this->memory->erase(this->memory->begin());

    // On récupère les paramètres qu'on stocks dans la mémoire de l'agent
    this->memory->push_back({state, next_state, reward, this->action, done});
  }

  std::vector<double> q_values = this->mlp->feed_forward(state);
  std::vector<double> next_q_values = this->target_network->feed_forward(next_state);
  
  double target = reward;
  if (done == false) // Si on est pas dans l'état final de l'agent, on calcule la pertinence de sa récompense
    target += this->gamma * (*std::max_element(next_q_values.begin(), next_q_values.end()));
  
  std::vector<double> target_vector = q_values;
  target_vector[this->action] = target;

  this->mlp->backward_propagate(target_vector, this->learning_rate);
}

void DQNAgent::train_long_term()
{
  // Si on a pas assez d'élément pour l'entrainement à long terme on ne fait rien
  if (this->memory->size() < this->batch_size) return;

  // On copie le résseau courant dans le réseau cible toute les 1000 itérations
  if (this->iteration % 10 == 0) *this->target_network = *this->mlp;

  // On incrémente le compteur d'essai de l'agent courant car on utilise cette méthode quand l'agent est mort
  this->iteration++;

  static std::random_device rd;
  static std::mt19937 gen(rd());

  // Sinon, on récupère un vecteur d'éléments sur lequel entrainer l'agent
  std::vector<Episodes> bach;
  std::sample(this->memory->begin(), this->memory->end(), std::back_inserter(bach), this->batch_size, gen);
  
  // Puis, on l'entraine
  for (size_t i = 0; i < bach.size(); ++i)
  {
    this->action = bach[i].action;
    this->train_short_term(bach[i].state, bach[i].reward, bach[i].next_state, bach[i].done, false);
  }
}

int DQNAgent::get_current_iteration() { return this->iteration; }
void DQNAgent::set_batch_size(const int &batch_size) { this->batch_size = batch_size; }
