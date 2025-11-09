#pragma once

#include <SDL2/SDL_render.h>
#include <ctime>
#include <algorithm>
#include <iostream>
#include "isometric_map.hpp"
#include "snake.hpp"

/**
 * @brief Classe gérant la logique de jeu globale
*/
class Game
{
  public:
    /**
     * @brief Constructeur de la classe Game, initialise le jeu
    */
    Game();

    /**
     * @brief Destructeur de la classe Game
    */
    ~Game();
    
    /**
     * @brief Méthode mettant à jour la logique de jeu, utile pour entrainer l'agent sans UI
     * @param direction: int, entrée de l'agent d'apprentissage pour le jeu
    */
    //void update(int direction);
    void update();
    
    /**
     * @brief Accesseur de l'état courant du jeu
     * @return std::vector<double>, vecteur contenant les informations dont l'agent a besoin pour s'entrainer, les formates pour l'agent
    */
    std::vector<double> get_game_state();
    
    /**
     * @brief Méthode permettant de savoir si le serpent a mangé une pomme durant la dernière itération
     * @return bool, true si oui, false sinon
    */
    bool the_snake_ate_an_apple();
    
    /**
     * @brief Accesseur du score de la partie courante
     * @return int, score courant
    */
    int get_score();

    /**
     * @brief Méthode gérant les entrées du jeu
     * @param direction: int, direction du snake sur la carte
    */
    void handle_inputs(int direction);

    /**
     * @brief Méthode chargé d'afficher le jeu global
     * @param renderer: SDL_Renderer, instance de rendu de la fenêtre de jeu
     * @param tileset: SDL_Texture, instance du tileset de la carte de jeu
    */
    void display(SDL_Renderer* renderer, SDL_Texture* tileset);

    bool game_over;
    
  private:

    /**
     * @brief Méthode permettant de générer une nouvelle pomme sur la carte
    */
    void generate_new_apple();
    
    int score;
    time_t start; // heure à laquelle la partie a commencé
    int kill_timer;

    bool apple_eaten; // vérifie qu'une pomme a été mangé
    
    int direction; // direction du serpent

    Snake *i_snake;
    IsometricMap *i_map;
    Position p_apple;
};
