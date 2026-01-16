#ifndef MAPENGINE_HEADER
#define MAPENGINE_HEADER

/**
 * Fichier contenant le coeur du moteur de carte isométrique.
 * le 29/12/2025
 * par Noé Poirier
*/

#include "camera.hpp"

#include <SDL2/SDL.h>

#include <vector>
#include <map>

/**
 * @brief Classe permettant de gérer une carte afficher en vue isométrique.
*/
class IsometricEngine
{
  public:
    /**
     * @brief Constructeur de la carte courante, construit le pointeur sur la caméra
    */
    IsometricEngine();
    
    /**
     * @brief Destructeur de la classe courante
    */
    ~IsometricEngine();

    /**
     * @brief Méthode permettant de modifier une tuile à une position donnée 
     * @param pos_x: int, position en x de la tuile à modifier sur la carte
     * @param pos_y: int, position en y de la tuile à modifier sur la carte
     * @param tile: char, tuile à modifier sur la carte
     * @return bool, retourne true si l'opération a réussi, false sinon
    */
    bool set_tile(const int &pos_x, const int &pos_y, const char &tile);

    /**
     * @brief Accesseur d'une tuile de la carte à la position en paramètre
     * @param pos_x: int, position en x de la tuile
     * @param pos_y: int, position en y de la tuile
     * @return char, retourne la tuile à la position en paramètre, '\n' si la position en paramètre n'est pas dans la carte
    */
    char get_tile(const int &pos_x, const int &pos_y);

    /**
     * @brief Accesseur de la carte courante
     * @return vector<vector<char>>, carte courante
    */
    std::vector<std::vector<char>> &get_map();

    /**
     * @brief Méthode d'affichage de la carte en vue isométrique, si aucune texture n'est chargé, on charge la texture d'exemple avec sa carte associé
     * @param renderer: SDL_Renderer, fenêtre d'affichage sdl courant
    */
    void display(SDL_Renderer* renderer);

    /**
     * @brief Accesseur de la caméra courante.
     * @return SDL_Rect, rectangle correspondant à la caméra
    */
    Camera *get_camera();

    /**
     * @brief Méthode permettant de charger une carte depuis un fichier
     * @param file_name: char, nom du fichier contenant la carte à charger
     * @return bool, retourne true si l'opération a réussi, false sinon
    */
    bool load_map_from_file(const char *file_name);

    /**
     * @brief Méthode permettant de charger une texture pour la carte depuis un fichier, la méthode ne décharge pas la texture courante tant qu'elle n'est pas sûr qu'il n'y aura pas d'erreurs.
     * @param file_name: char, nom du fichier contenant la texture à charger
     * @param renderer: SDL_Renderer, fenêtre de rendue SDL pour laquelle créer la texture
     * @return bool, renvoie true si la texture a chargé correctement, false sinon
    */
    bool load_texture_from_file(const char *file_name, SDL_Renderer *renderer);

    /**
     * @brief Méthode permettant de charger le contenu du fichier de configuration en paramètre
     * @param file_name: char, nom du fichier de configuration à charger
     * @param renderer: SDL_Renderer, fenêtre pour laquelle charger la texture dans le fichier de configuration
     * @return bool, renvoie true si la configuration a été appliquée correctement, false sinon
    */
    bool load_config_from_file(const char *file_name, SDL_Renderer *renderer);

    /**
     * @brief Méthode permettant de charger la configuration d'exemple du moteur d'affichage
     * @param renderer: SDL_Renderer, fenêtre de rendue pour laquelle charger la texture
    */
    void load_exemple_config(SDL_Renderer *renderer);

    /**
     * @brief Méthode permettant de charger le vecteur en paramètre en tant que nouvelle carte
     * @param map: vector<vector<char>>, nouvelle carte à attribuer
    */
    void set_as_new_map(const std::vector<std::vector<char>> &map);

    /**
     * @brief Mutateur global des échelles de rendue du moteur isométrique
     * @param x_scale : int, nouvelle échelle en x
     * @param y_scale : int, nouvelle échelle en y
    */
    void set_scale(const int &x_scale, const int &y_scale);

    /**
     * @brief Méthode permettant de définir une nouvelle échelle de rendue en x
     * @param x_scale: int, nouvelle échelle de rendue en x
    */
    void set_x_scale(const int &x_scale);

    /**
     * @brief Méhode permettant de définir une nouvelle échelle de rendue en y
     * @param y_scale: int, nouvelle échelle de rendue en y
    */
    void set_y_scale(const int &y_scale);

    /**
     * @brief Accesseur de l'échelle de référence d'affichage en x
     * @return int, échelle de référence de l'affichage en x
    */
    int &get_x_scale();

    /**
     * @brief Accesseur de l'échell de référence d'affichage en y
     * @return int, échelle de référence de l'affichage en y
    */
    int &get_y_scale();

    /**
     * @brief Mutateur de la texture de rendue courante
     * @param texture: SDL_Texture, nouvelle texture de rendue à attribuer
     * @return bool, retourne false si le pointeur en paramètre en un pointeur nul, false sinon
    */
    bool set_as_new_texture(SDL_Texture *texture);

    /**
     * @brief Mutateur des positions globales des textures en fonctions des caractères de la carte
     * @param shape: map<char, SDL_Rect>, nouvelle position globale des textures en fonction des caractère
    */
    void set_as_new_texture_shape(const std::map<char, SDL_Rect> &shape);

    /**
     * @brief Méthode permettnat d'ajouter ou modifier la forme d'une texture associé à un caractère
     * @param key: char, caractère associé à la texture à modifier ou ajouter
     * @param shape: SDL_Rect, paramètre de la texture à ajouter ou modifier
    */
    void add_texture_shape(const char &key, const SDL_Rect &shape);

  private:
    std::vector<std::vector<char>> map;
    
    Camera *camera; // caméra courante
    
    SDL_Texture *texture;
    std::map<char, SDL_Rect> texture_shape;

    // échelle de référence pour uniformiser l'affichage
    int x_scale; // échelle en x
    int y_scale; // échelle en y
};

#endif // !MAPENGINE_HEADER

