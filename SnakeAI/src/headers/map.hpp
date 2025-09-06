#pragma once

#include <ncurses.h>
#include "global.hpp"

/**
 * @brief Classe chargé de gérer la carte dans son ensemble
*/
class Map
{
  public:
    /**
     * @brief Constructeur de la carte
     * @param height: int, hauteur de la carte
     * @param width: int, largeur de la carte
    */
    Map(int height, int width);

    /**
     * @brief Destructeur de la carte
    */
    ~Map();
    
    /**
     * @brief Méthode permettant d'afficher la carte en utilisant ncurses
    */
    void display();
    
    /**
     * @brief Accesseur de la valeur d'une tuile de la carte
     * @param pos: Position, position de la tuile que l'on veut récupérer
     * @return int, valeur de la tuile que l'on veut récupérer, renvoie -1 si on est en dehors de la carte
    */
    int get_tile(Position pos);

    /**
     * @brief Mutateur de la carte
     * @param pos: Position, position de la tuile à modifier, ne fait si la position est en dehors de la carte
     * @param value: int, valeur à attribuer à la carte à la position voulue
    */
    void set_tile(Position pos, int value);

    /**
     * @brief Méthodfe effaçant le contenu de la carte
    */
    void set_blank();

  private:
    int **tilemap; // tableau contenant la carte
    int width; // largeur du tableau
    int height; // hauteur du tableau
    char tileset[6] = " EASH"; // caractères à afficher sur la carte
};
