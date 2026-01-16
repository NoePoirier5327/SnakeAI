#ifndef TEXT_HEADER
#define TEXT_HEADER

/**
 * Fichier contenant la classe gérant une zone de texte sur l'affichage.
 * le 2/01/2026
 * par Noé Poirier
*/

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>

#include <string>

/**
 * @brief Classe gérant une zone de texte sur l'affichage SDL2, on considère que la librairie SDL2 et sa composante TTF sont correctement initialisées avant de se servir de cette classe
*/
class Text
{
  public:
    /**
     * @brief Constructeur de la classe courante, charge la police et la surface de rendue SDL2
     * @param text: string, texte à afficher par l'instance courante
     * @param pos_x: int, position en x du texte
     * @param pos_y: int, position en y du texte
     * @param font_name: string, police de caractère à charger
     * @param font_size: int, taille de la police à charger
     * @param color: SDL_Color, couleur du texte à afficher
     * @param renderer: SDL_Renderer, fenêtre de rendue pour laquelle créer le texte
    */
    Text(const std::string &text, const int &pos_x, const int &pos_y, const std::string &font_name, const int &font_size, const SDL_Color &color, SDL_Renderer *renderer);

    /**
     * @brief Destructeur de la classe courante, décharge la police de rendue et la surface d'affichage
    */
    ~Text();

    /**
     * @brief Méthode d'affichage du texte courant sur la fenêtre d'affichage
     * @param renderer: SDL_Renderer, fenêtre de rendue courante
     * @return bool, renvoie true si l'opération a réussie, false sinon
    */
    bool display(SDL_Renderer *renderer);

    /**
     * @brief Méthode permettant de charger une police de caractère pour l'affichage
     * @param font_name: string, chemin de la police à charger
     * @param font_size: int, taille de la police à charger
     * @return bool, retourne true si l'action s'est bien passée, false sinon
    */
    bool load_font(const std::string &font_name, const int &font_size);

    /**
     * @brief Accesseur du nom de la police de caractère courante
     * @return string, police de caractère courante
    */
    std::string &get_font_name();

    /**
     * @brief Accesseur de la taille de la police d'écriture.
     * @return int, taille de la police d'écriture
    */
    int &get_font_size();

    /**
     * @brief Mutateur du texte afficher par l'instance courante
     * @param text: string, nouveau texte à afficher
     * @param renderer: SDL_Renderer, fenêtre de rendue pour laquelle préparer la texture d'affichage
     * @return bool, renvoie true s'il n'y a aucune erreur, false sinon
    */
    bool set_text(const std::string &text, SDL_Renderer *renderer);

    /**
     * @brief Accesseur du texte à afficher par l'instance courante
     * @return string, nouveau texte
    */
    std::string &get_text();

    /**
     * @brief Mutateur de la couleur du texte courant
     * @param color: SDL_Color, nouvelle couleur du texte
    */
    void set_text_color(const SDL_Color &color);

    /**
     * @brief Accesseur de la couleur courante du texte
     * @return SDL_Color, couleur courante du texte
    */
    SDL_Color &get_text_color();

    /**
     * @brief Mutateur de la position du texte sur l'affichage courant
     * @param pos_x: int, nouvelle position du texte en x
     * @param pos_y: int, nouvelle position du texte en y
    */
    void set_pos(const int &pos_x, const int &pos_y);

    /**
     * @brief Mutateur de la position en x du texte
     * @param pos_x: int, nouvelle position du texte en x
    */
    void set_pos_x(const int &pos_x);

    /**
     * @brief Mutateur de la position en y du texte
     * @param pos_y: int, nouvelle position du texte en y
    */
    void set_pos_y(const int &pos_y);

    /**
     * @brief Accesseur de la position en x du texte
     * @return int, position en x du texte
    */
    int &get_pos_x();

    /**
     * @brief Accesseur de la position en y du texte
     * @return int, position en y du texte
    */
    int &get_pos_y();

  private:
    SDL_Rect rect; // Rectangle d'affichage du texte

    std::string font_name;
    int font_size;
    std::string text;

    SDL_Color text_color;

    TTF_Font *font;
    SDL_Surface *surface;
    SDL_Texture *texture;
};

#endif // !TEXT_HEADER
