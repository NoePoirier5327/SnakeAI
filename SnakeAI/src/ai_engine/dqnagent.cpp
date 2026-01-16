/**
 * Fichier contenant l'implémentation d'un agent d'apprentissage profond
 * en 2025
 * par Noé Poirier
*/

#include "dqnagent.hpp"

const static float EPSILON_END = 0.05;
const static float EPSILON_DECAY = 0.95;
const static int BACH_SIZE = 256;
const static int MAX_MEMORY_SIZE = 100000;
const static int CONVERGENCE_COUNTER = 100;

DQNAgent::DQNAgent(std::vector<int>& net_shape, float lr, float epsilon, float gamma)
{
  this->mlp = new MLP(net_shape);
  this->target_network = new MLP(net_shape);
  
  this->nb_action = net_shape.back();
  this->learning_rate = lr;
  this->epsilon = epsilon;
  this->gamma = gamma;

  this->iteration = 1;

  this->memory = new std::vector<Episodes>;
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
  if (this->iteration % CONVERGENCE_COUNTER == 0)
    this->epsilon = std::max(EPSILON_END, static_cast<float>(this->epsilon - pow(10, -5)));

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
    // Si on dépasse la mémoire autorisé pour la mémoire de l'agent, on supprime son premier élément
    if (this->memory->size() >= MAX_MEMORY_SIZE) this->memory->erase(this->memory->begin());

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
  if (this->memory->size() < BACH_SIZE) return;

  // On copie le résseau courant dans le réseau cible toute les 1000 itérations
  if (this->iteration % 10 == 0) *this->target_network = *this->mlp;

  // On incrémente le compteur d'essaie de l'agent courant car on utilise cette méthode quand l'agent est mort
  this->iteration++;

  static std::random_device rd;
  static std::mt19937 gen(rd());

  // Sinon, on récupère un vecteur d'éléments sur lequel entrainer l'agent
  std::vector<Episodes> bach;
  std::sample(this->memory->begin(), this->memory->end(), std::back_inserter(bach), BACH_SIZE, gen);
  
  // Puis, on l'entraine
  for (size_t i = 0; i < bach.size(); ++i)
  {
    this->action = bach[i].action;
    this->train_short_term(bach[i].state, bach[i].reward, bach[i].next_state, bach[i].done, false);
  }
}

int DQNAgent::get_current_iteration() { return this->iteration; }
