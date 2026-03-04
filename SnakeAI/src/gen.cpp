/**
 * Fichier contenant l'implémentation d'un algorithme génétique
 * en décembre 2025
 * par Noé Poirier
*/

#include "gen.hpp"
#include "ai_engine/dqnagent.hpp"
#include "game.hpp"
#include <SDL2/SDL_render.h>
#include <cstdlib>

// @brief Représente les paramètres d'un agent d'apprentissage
struct AgentParams
{
  std::vector<int> net_shape;
  float learning_rate;
  float epsilon;
  float gamma;
  int batch_size;
  int memory_size;
  float epsilon_decay;
  float epsilon_end;
  int convergence_counter;
};

const static Direction DIRECTIONS[4] = {haut, bas, gauche, droite};

/**
 * @brief Fonction chargé de générer aléatoirement une population de n individus.
 * @param agents : std::vector<DQNAgent *>, ensemble des agents généré par la fonction, si non vide, est vidé par la fonction avant affectation
 * @param actifs : std::map<int, bool>, permet de savoir, en fonction de son index dans la population, l'état actif ou non d'un agent quelconque
 * @param population : int, taille de la population à générer
 * @return std::vector<AgentParams>, ensemble des paramètres de générations de la populations courante.
*/
std::vector<AgentParams> generate_random_population(std::vector<DQNAgent *> &agents, std::map<int, bool> &actifs, const int& population)
{
  // On vide et désalloue les éventuelles agents précédents
  while (agents.size() > 0)
  {
    if (agents.back() != nullptr)
      delete agents.back();
    agents.pop_back();
  }

  // On génére la population en stockant ses paramètres
  std::vector<AgentParams> params;
  params.reserve(population);

  for (int i = 0; i < population; ++i)
  {
    std::vector<int> net = {77};

    int n = int_rng(1, 10);
    for (int j = 0; j < n; ++j)
      net.push_back(int_rng(1, 256));

    net.push_back(4);

    params.push_back({net, 0, 0, 0, 0, 0, 0, 0, 0});
    params.back().learning_rate = rng(0, 1);
    params.back().epsilon = rng(0, 1);
    params.back().gamma = rng(0, 1);
    params.back().batch_size = int_rng(1, 512);
    params.back().memory_size = int_rng(1, 200000);
    params.back().epsilon_decay = rng(0, 1);
    params.back().epsilon_end = rng(0, 1);
    params.back().convergence_counter = int_rng(1, 1000);

    actifs[i] = true;

    agents.push_back(new DQNAgent(net, params.back().learning_rate, params.back().epsilon, params.back().gamma, params.back().batch_size, params.back().memory_size, params.back().epsilon_decay, params.back().epsilon_end, params.back().convergence_counter));
  }

  return params;
}

/**
 * @brief Fonction générant les environnements dans lesquelles les agents vont s'entrainer
 * @param population: int, nombre d'environnements à générer
 * @param renderer : SDL_Renderer, fenêtre d'affichage des environnements
 * @return std::vector<Game *>, ensemble des instances des environnements des agents d'apprentissage
*/
std::vector<Game*> generate_environnements(const int &population, SDL_Renderer *renderer)
{
  std::vector<Game *> environnements;
  for (int i = 0; i < population; ++i)
    environnements.push_back(new Game(renderer));
  return environnements;
}

/**
 * @brief Fonction permettant de savoir quel est le meilleur agent d'une population, c'est à dire, celui qui a le plus de points une fois que toute la population est morte.
 * @param environnements: std::vector<Game *>, environnements dans lesquelles ont évolués les agents
 * @return int, index de du meilleur agent, renvoie -1 si les environnements sont vides
*/
int index_of_best_agent_in_population(const std::vector<Game *> &environnements)
{
  int index = 0;
  int best_score = (environnements.size() <= 0 ? -1 : environnements[0]->get_score());
  for (int i = 0; i < environnements.size(); ++i)
  {
    if (best_score < environnements[i]->get_score())
    {
      index = i;
      best_score = environnements[i]->get_score();
    }
  }
  return (environnements.size() <= 0 ? -1 : index);
}

void genetic_algorithm(std::vector<int> &net_shape, float &learning_rate, float &epsilon, float &gamma, int &batch_size, int &memory_size, float &epsilon_decay, float &epsilon_end, int &convergence_counter, int population, int nb_gen, int &best_score, int &gen_best_score, SDL_Renderer *renderer)
{
  // On commence par créer la première population d'agents d'apprentissage avec des paramètres d'entrées totalement aléatoires
  // ainsi que leurs environnements d'apprentissage associés
  std::vector<DQNAgent *> agents;
  std::vector<Game *> environnments = generate_environnements(population, renderer);
  std::map<int, bool> actifs; // dictionnaire auquel on associe l'état actif ou non d'un agent
  std::vector<AgentParams> params = generate_random_population(agents, actifs, population);

  // Maintenant, on fait jouer et on entraine les agents sur leurs environnements respectifs
  // et lorsqu'ils sont tous morts, on recréer le vecteur agents avec de nouveaux agents combinant les caractéristiques du meilleur agent avec un agent aléatoire ainsi qu'un nombre aléatoire de caracteristiques aléatoire
  for (int gen = 0; gen < nb_gen; ++gen)
  {
    int nb_actifs = population; // On garde une trace du nombre d'agents qui n'est pas encore mort dans la population courante

    // On fait jouer les agents dans leurs environnements tant qu'ils ne sont pas tous morts
    while (nb_actifs > 0)
    {
      for (int i = 0; i < population; ++i)
      {
        // Si le jeu est fini pour l'agent courant et qu'il est encore actif,
        // Alors, on le désactive et baisse le compteur d'agents actifs
        if (environnments[i]->game_over == true && actifs[i] == true)
        {
          nb_actifs --;
          actifs[i] = false;
        }

        // Sinon, on fait se dérouler un tour normalement
        if (!environnments[i]->game_over)
        {
          // 1. On récupère l'état courant et fait décider l'agent d'apprentissage
          std::vector<double> state = environnments[i]->get_game_state();
          environnments[i]->handle_inputs(DIRECTIONS[agents[i]->decide(state)]);

          // 2. On met à jour la logique de l'environnement courant
          environnments[i]->update();

          // 3. On le récompense en fonction des conséquences de sa dernière action
          std::vector<double> next_state = environnments[i]->get_game_state();

          // S'il a mangé une pomme, on le récompense de 10 points
          if (environnments[i]->the_snake_ate_an_apple())
            agents[i]->train_short_term(state, 10.0, next_state, environnments[i]->game_over);

          // S'il est mort, on le sanctionne de 1 point et l'entraine à long terme
          else if (environnments[i]->game_over)
          {
            agents[i]->train_short_term(state, -1, next_state, environnments[i]->game_over);
            agents[i]->train_long_term();
          }

          // S'il n'a rien fait, on le sanctionne de 0.1 point
          else
            agents[i]->train_short_term(state, -0.1, next_state, environnments[i]->game_over);
        }
      }
    }

    // Maintenant, on détermine l'agent aillant fait le meilleur score
    int best_agent_index = index_of_best_agent_in_population(environnments);

    // Ensuite, on détermine un agent aléatoire (qui n'est pas le meilleur agent), pour créer une nouvelle population
    int random_agent_index;

    do { random_agent_index = int_rng(0, population); }
    while (random_agent_index != best_agent_index);

    // Enfin, on applique la notion d'algorithme génétique pour créer la nouvelle population
    // On détermine les paramètres de création de la nouvelle population
    AgentParams params[population];
    for (int i = 0; i < population; ++i)
    {
      params[i].net_shape = (int_rng(0, 1) == 0 ? net_shapes[best_agent_index] : net_shapes[random_agent_index]);
      params[i].learning_rate = (int_rng(0, 1) == 0 ? learning_rates[best_agent_index] : learning_rates[random_agent_index]);
      params[i].epsilon = (int_rng(0, 1) == 0 ? epsilons[best_agent_index] : epsilons[random_agent_index]);
      params[i].gamma = (int_rng(0, 1) == 0 ? gammas[best_agent_index] : gammas[random_agent_index]);
      params[i].batch_size = (int_rng(0, 1) == 0 ? batch_sizes[best_agent_index] : batch_sizes[random_agent_index]);
      params[i].memory_size = (int_rng(0, 1) == 0 ? memory_sizes[best_agent_index] : memory_sizes[random_agent_index]);
      params[i].epsilon_decay = (int_rng(0, 1) == 0 ? epsilons_decay[best_agent_index] : memory_sizes[random_agent_index]);
      params[i].epsilon_end = (int_rng(0, 1) == 0 ? epsilons_end[best_agent_index] : epsilons_end[random_agent_index]);
      params[i].convergence_counter = (int_rng(0, 1) == 0 ? convergence_counters[best_agent_index] : convergence_counters[random_agent_index]);
    }

    // On applique les nouveaux paramètres en recréant une population
    for (int i = 0; i < population; ++i)
    {
      delete agents[i];
      agents[i] = new DQNAgent(params[i].net_shape, params[i].learning_rate, params[i].epsilon, params[i].gamma, params[i].batch_size, params[i].memory_size, params[i].epsilon_decay, params[i].epsilon_end, params[i].convergence_counter);

      delete environnments[i];
      environnments[i] = new Game(renderer);

      // On récupère les paramètres de création
      net_shapes[i] = params[i].net_shape;
      learning_rates[i] = params[i].learning_rate;
      epsilons[i] = params[i].epsilon;
      gammas[i] = params[i].gamma;
      batch_sizes[i] = params[i].batch_size;
      memory_sizes[i] = params[i].memory_size;
      epsilons_decay[i] = params[i].epsilon_decay;
      epsilons_end[i] = params[i].epsilon_end;
      convergence_counters[i] = params[i].convergence_counter;
    }
  }
}
