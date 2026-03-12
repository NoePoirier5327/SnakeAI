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
 * @brief Fonction chargé de créer une population d'agent associé à des environnements de jeu à partir des paramètres en paramètres.
 * @param agents : std::vector<DQNAgent*>, tableau modifié pour avoir la nouvelle population d'agents
 * @param environnements, std::vector<Game*>, tableau modifié pour avoir les nouveaux environnements de jeu pour les IA
 * @param params : std::vector<AgentParams>, paramètres de création pour la nouvelle population d'agents
 * @param renderer : SDL_Renderer, fenêtre d'affichage des environnements
*/
void generate_population_with_params(std::vector<DQNAgent*> &agents, std::vector<Game*> &environnements, const std::vector<AgentParams> &params, SDL_Renderer *renderer)
{
  size_t n = params.size();
  for (size_t i = 0; i < n; ++i)
  {
    if (agents.size() < n)
      agents.push_back(new DQNAgent(params[i].net_shape, params[i].learning_rate, params[i].epsilon, params[i].gamma, params[i].batch_size, params[i].memory_size, params[i].epsilon_decay, params[i].epsilon_end, params[i].convergence_counter));
    else if (agents[i] != nullptr)
    {
      delete agents[i];
      agents[i] = new DQNAgent(params[i].net_shape, params[i].learning_rate, params[i].epsilon, params[i].gamma, params[i].batch_size, params[i].memory_size, params[i].epsilon_decay, params[i].epsilon_end, params[i].convergence_counter);
    }
    else
       agents[i] = new DQNAgent(params[i].net_shape, params[i].learning_rate, params[i].epsilon, params[i].gamma, params[i].batch_size, params[i].memory_size, params[i].epsilon_decay, params[i].epsilon_end, params[i].convergence_counter);

    if (environnements.size() < n)
      environnements.push_back(new Game(renderer));
    else if (environnements[i] != nullptr)
    {
      delete environnements[i];
      environnements[i] = new Game(renderer);
    }
    else
       environnements[i] = new Game(renderer);
  }
}

/**
 * @brief Fonction permettant de créer un nouvelle ensemble de paramètres à partir duquel on va créer une nouvelle population à partir des indexs du meilleur agent et d'un agent aléatoire.
 * @param i1: int, index du meilleur agent ou de l'agent aléatoire (l'ordre n'a pas d'incidence).
 * @param i2: int, pareille ici
*/
void combine_params(std::vector<AgentParams> &params, const int &i1, const int &i2)
{
  for (size_t i = 0; i < params.size(); ++i)
  {
    if (i != i1 || i != i2)
    {
      params[i].net_shape = (int_rng(0, 1) == 0 ? params[i1].net_shape : params[i2].net_shape);
      params[i].learning_rate = (int_rng(0, 1) == 0 ? params[i1].learning_rate : params[i2].learning_rate);
      params[i].epsilon = (int_rng(0, 1) == 0 ? params[i1].epsilon : params[i2].epsilon);
      params[i].gamma = (int_rng(0, 1) == 0 ? params[i1].gamma : params[i2].gamma);
      params[i].batch_size = (int_rng(0, 1) == 0 ? params[i1].batch_size : params[i2].batch_size);
      params[i].memory_size = (int_rng(0, 1) == 0 ? params[i1].memory_size : params[i2].memory_size);
      params[i].epsilon_decay = (int_rng(0, 1) == 0 ? params[i1].epsilon_decay : params[i2].epsilon_decay);
      params[i].epsilon_end = (int_rng(0, 1) == 0 ? params[i1].epsilon_end : params[i2].epsilon_end);
      params[i].convergence_counter = (int_rng(0, 1) == 0 ? params[i1].convergence_counter : params[i2].convergence_counter);
    }
  }
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

/**
 * @brief Fonction permettant aux agents en paramètre de jouer un tour dans leurs environnements respectifs.
 * @param environnements : std::vector<Game*>, environnements dans lesquelles les agents vont jouer.
 * @param agents : std::vector<DQNAgent*>, agents qui vont jouer dans leurs environnements respectifs.
 * @param population : int, taille de la population de joueur
 * @param nb_enable : int, nombre d'agents actifs parmis la population de joueur
 * @param actifs : std::map<int, bool>, permet de savoir si l'agent courant est atifs ou non
*/
void play_one_time(const std::vector<Game*> &environnements, const std::vector<DQNAgent*> &agents, const int &population, int &nb_enable, std::map<int, bool> &actifs)
{
  for (int i = 0; i < population; ++i)
  {
    // Si le jeu est fini pour l'agent courant et qu'il est encore actif,
    // Alors, on le désactive et baisse le compteur d'agents actifs
    if (environnements[i]->game_over == true && actifs[i] == true)
    {
      nb_enable --;
      actifs[i] = false;
    }

    // Sinon, on fait se dérouler un tour normalement
    if (!environnements[i]->game_over)
    {
      // 1. On récupère l'état courant et fait décider l'agent d'apprentissage
      std::vector<double> state = environnements[i]->get_game_state();
      environnements[i]->handle_inputs(DIRECTIONS[agents[i]->decide(state)]);

      // 2. On met à jour la logique de l'environnement courant
      environnements[i]->update();

      // 3. On le récompense en fonction des conséquences de sa dernière action
      std::vector<double> next_state = environnements[i]->get_game_state();

      // S'il a mangé une pomme, on le récompense de 10 points
      if (environnements[i]->the_snake_ate_an_apple())
        agents[i]->train_short_term(state, 10.0, next_state, environnements[i]->game_over);

      // S'il est mort, on le sanctionne de 1 point et l'entraine à long terme
      else if (environnements[i]->game_over)
      {
        agents[i]->train_short_term(state, -1, next_state, environnements[i]->game_over);
        agents[i]->train_long_term();
      }

      // S'il n'a rien fait, on le sanctionne de 0.1 point
      else
        agents[i]->train_short_term(state, -0.1, next_state, environnements[i]->game_over);
    }
  }
}

AgentParams genetic_algorithm(const int &population, const int &nb_gen, SDL_Renderer *renderer)
{
  // On commence par créer la première population d'agents d'apprentissage avec des paramètres d'entrées totalement aléatoires
  // ainsi que leurs environnements d'apprentissage associés
  std::vector<DQNAgent *> agents;
  std::vector<Game *> environnments = generate_environnements(population, renderer);
  std::map<int, bool> actifs; // dictionnaire auquel on associe l'état actif ou non d'un agent
  std::vector<AgentParams> params = generate_random_population(agents, actifs, population);
  int best_agent_index = -1;

  // Maintenant, on fait jouer et on entraine les agents sur leurs environnements respectifs
  // et lorsqu'ils sont tous morts, on recréer le vecteur agents avec de nouveaux agents combinant les caractéristiques du meilleur agent avec un agent aléatoire ainsi qu'un nombre aléatoire de caracteristiques aléatoire
  for (int gen = 0; gen < nb_gen; ++gen)
  {
    int nb_actifs = population; // On garde une trace du nombre d'agents qui n'est pas encore mort dans la population courante

    // On fait jouer les agents dans leurs environnements tant qu'ils ne sont pas tous morts
    while (nb_actifs > 0)
      play_one_time(environnments, agents, population, nb_actifs, actifs);

    // Maintenant, on détermine l'agent aillant fait le meilleur score
    best_agent_index = index_of_best_agent_in_population(environnments);

    // Ensuite, on détermine un agent aléatoire (qui n'est pas le meilleur agent), pour créer une nouvelle population
    int random_agent_index;

    do { random_agent_index = int_rng(0, population); }
    while (random_agent_index != best_agent_index);

    // Enfin, on applique la notion d'algorithme génétique pour créer la nouvelle population
    // On détermine les paramètres de création de la nouvelle population
    combine_params(params, best_agent_index, random_agent_index);

    // On applique les nouveaux paramètres en recréant une population
    generate_population_with_params(agents, environnments, params, renderer);
  }

  return params[best_agent_index];
}
