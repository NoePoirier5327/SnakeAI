#pragma once

#include <ctime>
#include <algorithm>
#include "map.hpp"
#include "snake.hpp"

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
     * @param direction: int, entrée de l'agent d'apprentissage dans le jeu
    */
    void play(int direction);
    
    /**
     * @brief Méthode mettant à jour la logique de jeu, utile pour entrainer l'agent sans UI
     * @param direction: int, entrée de l'agent d'apprentissage pour le jeu
    */
    void update(int direction);
    
    /**
     * @brief Accesseur de l'état courant du jeu
     * @return std::vector<double>, vecteur contenant les informations dont l'agent a besoin pour s'entrainer, les formates pour l'agent
    */
    std::vector<double> get_game_state();

    /**
     * @brief Méthode déterminant si le jeu est fini ou non
     * @return bool, true si le jeu est fini, false sinon
    */
    bool the_game_is_over();
    
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

  private:
    /**
     * @brief Méthode gérant les entrées du jeu
    */
    void handle_inputs();

    /**
     * @brief Méthode chargé d'afficher le jeu global
    */
    void display();
    
    /**
     * @brief Méthode permettant de générer une nouvelle pomme sur la carte
    */
    void generate_new_apple();

    int w_height; // hauteur de la fenêtre de jeu
    int w_width; // largeur de la fenêtre de jeu
    
    int score;
    time_t start; // heure à laquelle la partie a commencé

    bool game_over; // contient l'état global du jeu
    bool apple_eaten; // vérifie qu'une pomme a été mangé
    
    int direction; // direction du serpent

    Snake *i_snake;
    Map *i_map;
    Position p_apple;
};
