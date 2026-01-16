#pragma once

/**
 * Fichier contenant la déclaration d'une classe gérant le jeu snake
 * en 2025
 * par Noé Poirier
*/

#include "snake.hpp"
#include "isometric_engine/isometric_engine.hpp"

#include <SDL2/SDL_render.h>

#include <ctime>
#include <algorithm>
#include <iostream>

/**
 * @brief Classe gérant la logique de jeu globale
*/
class Game
{
  public:
    /**
     * @brief Constructeur de la classe Game, initialise le jeu
     * @param map_width: int, largeur de la carte à charger
     * @param map_height: int, hauteur de la carte à charger
     * @param renderer: SDL_Renderer, fenêtre de rendue pour laquelle charger la carte
    */
    Game(const int &map_width, const int &map_height, SDL_Renderer *renderer);

    /**
     * @brief Destructeur de la classe Game
    */
    ~Game();
    
    /**
     * @brief Méthode mettant à jour la logique de jeu, utile pour entrainer l'agent sans UI
    */
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
    int& get_score();

    /**
     * @brief Méthode gérant les entrées du jeu
     * @param direction: Direction, direction du snake sur la carte
    */
    void handle_inputs(const Direction &direction);

    /**
     * @brief Méthode chargé d'afficher le jeu global
     * @param renderer: SDL_Renderer, instance de rendu de la fenêtre de jeu
    */
    void display(SDL_Renderer* renderer);

    bool game_over;
    
  private:

    /**
     * @brief Méthode permettant de générer une nouvelle pomme sur la carte
    */
    void generate_new_apple();
    
    int score;
    bool apple_eaten; // vérifie qu'une pomme a été mangé

    std::vector<std::vector<char>> empty_map;
    
    Direction direction; // direction du serpent

    Snake *i_snake;
    IsometricEngine *i_map;
    Position p_apple;
};
