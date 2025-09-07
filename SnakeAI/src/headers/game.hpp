#pragma once

#include <ctime>
#include "map.hpp"
#include "snake.hpp"
#include "apple.hpp"

/**
 * @brief Classe gérant la logique de jeu globale
*/
class Game
{
  public:
    /**
     * @brief Constructeur de la classe Game, initialise le jeu
     * @param height: int, hauteur de la carte en tile, permet de générer la position du serpent et de la pomme
     * @param width: int, largeur de la carte en tile, même fonction ici
    */
    Game(int height, int width);

    /**
     * @brief Destructeur de la classe Game
    */
    ~Game();
    
    /**
     * @brief Méthode permettant de lancer une itération du jeu
    */
    void run();

    /**
     * @brief Méthode déterminant si le jeu est fini ou non
     * @return bool, true si le jeu est fini, false sinon
    */
    bool the_game_is_over();

  private:
    /**
     * @brief Méthode gérant les entrées clavier du jeu
    */
    void handle_inputs();

    /**
     * @brief Méthode mettant à jour la logique de jeu
    */
    void update();

    /**
     * @brief Méthode chargé d'afficher le jeu global
    */
    void display();
    
    /**
     * @brief Méthode permettant de définir si le serpent est mort ou non
     * @return bool, si true, le serpent est mort, sinon, non
    */
    bool the_snake_is_dead();

    int w_height; // hauteur de la fenêtre de jeu
    int w_width; // largeur de la fenêtre de jeu
    
    int score;
    time_t start; // heure à laquelle la partie a commencé

    bool game_over; // contient l'état global du jeu
    
    int direction;

    Snake *i_snake;
    Map *i_map;
    Apple *i_apple;
};
