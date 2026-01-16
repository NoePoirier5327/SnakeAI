/**
 * Fichier contenant l'implémentation d'un algorithme génétique
 * en décembre 2025
 * par Noé Poirier
*/

#include "gen.hpp"
#include "ai_engine/dqnagent.hpp"
#include "game.hpp"

void genetic_algorithm(std::vector<int> &net_shape, float &learning_rate, float &epsilon, float &gamma, int &batch_size, int &memory_size, float &epsilon_decay, float &epsilon_end, int &convergence_counter, int population, int nb_gen, int &best_score, int &gen_best_score, SDL_Renderer *renderer)
{
    // On commence par créer la première population d'agents d'apprentissage avec des paramètres d'entrées totalement aléatoires
    // ainsi que leurs environnements d'apprentissage associés
    std::vector<DQNAgent *> agents;
    std::vector<Game *> environnments;

    for (int i = 0; i < population; ++i)
    {
        // D'abord l'environnement d'apprentissage
        environnments.push_back(new Game(renderer));

        // Ensuite les agents
        std::vector<int> net = {77}; // On a forcément 77 entrées

        int n = int_rng(1, 10); // Il y aura forcément entre 1 et 10 couches cachées
        for (int j = 0; j < n; ++j)
            net.push_back(int_rng(1, 256)); // Il y aura forcément entre 1 et 256 neurones par couches cachées

        net.push_back(4); // et on a forcément 4 sorties

        agents.push_back(new DQNAgent(net, rng(0, 1), rng(0,1), rng(0, 1), int_rng(1, 512), int_rng(1, 200000), rng(0, 1), rng(0, 1), int_rng(1, 1000)));
    }

    // Maintenant, on fait jouer et on entraine les agents sur leurs environnements respectifs
    // et lorsqu'ils sont tous morts, on recréer le vecteur agents avec de nouveaux agents combinant les caractéristiques des deux derniers meilleurs agents ainsi qu'un nombre aléatoire de caracteristiques aléatoire
    for (int gen = 0; gen < nb_gen; ++gen)
    {
        int nb_actifs = population; // On garde une trace du nombre d'agents qui n'est pas encore mort dans la population courante

        // On fait jouer les agents dans leurs environnements tant qu'ils ne sont pas mort
        while (nb_actifs > 0)
        {
            for (int i = 0; i < population; ++i)
            {
                if (environnments[i]->game_over == true)
                    nb_actifs --;
            }
        }
    }
}
