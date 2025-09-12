#include "headers/game.hpp"
#include "headers/dqnagent.hpp"
#include <cstring>
#include <ctime>
#include <ncurses.h>
#include <thread>

int main()
{
// On déclare nos variables
  std::vector<int> net_shape = {31, 128, 150, 200, 200, 150, 128, 4};
  std::vector<double> state; state.reserve(net_shape[0]);
  std::vector<double> next_state; next_state.reserve(net_shape[0]);
  int w_width = 15; int w_height = 15; int best_score = 0;
  int nb_iterations = 0; int best_iteration;
  
  // On instancie le jeu et l'agent d'apprentissage
  DQNAgent* bob = new DQNAgent(net_shape);
  Game *game = new Game(w_height, w_width);
  
  printf("Bonjour, bienvenue sur l'outil d'apprentissage de BOB.\n");
  printf("Veuillez choisir le nombre d'itérations pour l'entrainement de BOB sur le jeu snake : "); scanf("%d", &nb_iterations);
  printf("Entrainement de BOB sur %d d'itérations.\n", nb_iterations);
  
  // début de l'entrainement de BOB
  int start = time(nullptr);

  for (int i = 0; i < nb_iterations; i++)
  {
    while (game->the_game_is_over() == false)
    {
      state = game->get_game_state();
      game->update(bob->decide(state));
      next_state = game->get_game_state();

      if (game->the_snake_ate_an_apple() == true) bob->train(state, 2, next_state, false);
      else bob->train(state, 0, next_state, false);
    }

    if (best_score < game->get_score())
    {
      best_score = game->get_score();
      best_iteration = i;
      bob->train(state, 10, next_state, false);
    }
    else
      bob->train(state, -2, next_state, false);

    delete game;
    game = new Game(w_height, w_width);
  }

  int finish = time(nullptr);

  char test[1];
  bool run;
  printf("Temp d'entrainement de BOB : %d\n", start - finish);

  do
  {
    run = false;
    printf("Voulez-vous voir le test de l'entrainement de BOB (o/n) : "); scanf("%s", test);

    if (std::strcmp(test, "o") == true || std::strcmp(test, "n") == true)
    {
      run = true; printf("Mauvais format de réponse, rééssayez.\n");
    }
  } 
  while (run);

  if (std::strcmp(test, "o"))
  {
    // Lancement de ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    start = time(nullptr);
  
    // Boucle d'entrainement de l'agent
    while (game->the_game_is_over() == false)
    {
      state = game->get_game_state();
      game->play(bob->decide(state));
    
      std::this_thread::sleep_for(std::chrono::milliseconds(250));

      finish = time(nullptr) - start;
    
      move(0, w_width * 2); printw("Snake");
      move(1, w_width * 2); printw(" Score : %d", game->get_score());
      move(2, w_width * 2); printw(" Best score : %d", best_score);
      move(3, w_width * 2); printw(" Time : %ds", finish);
      move(4, w_width * 2); printf(" Itération : %d", nb_iterations+1);
    }

    getch();

    delete game;
    delete bob;
    endwin();
  }

  printf("Meilleur score : %d\nItération associé : %d\n", best_score, best_iteration);

  return 0;
}
