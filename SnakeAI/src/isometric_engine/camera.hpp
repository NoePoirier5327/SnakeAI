#ifndef CAMERA_HEADER
#define CAMERA_HEADER

/**
 * Fichier contenant les déclarations par rapport à la caméra dans l'affichage
 * le 29/12/2025
 * par Noé Poirier
*/

/**
 * @brief Classe gérant la caméra dans l'affichage de la carte
*/
class Camera
{
  public:
    /**
     * @brief Constructeur de la caméra courante
     * @param pos_x: int, position en x de la caméra
     * @param pos_y: int, position en y de la caméra
     * @param zoom: float, coefficient d'agrandissement de l'affichage
    */
    Camera(const int &pos_x, const int &pos_y, float &zoom);

    /**
     * @brief Mutateur de la position de la caméra.
     * @param pos_x: int, nouvelle position en x de la caméra
     * @param pos_y: int, nouvelle position en y de la caméra
    */
    void set_pos(const int &pos_x, const int &pos_y);

    /**
     * @brief Mutateur de la position en x de la caméra
     * @param x: float, nouvelle position en x
    */
    void set_pos_x(const float &x);

    /**
     * @brief Mutateur de la position en y de la caméra
     * @param y: flaot, nouvelle position en y
    */
    void set_pos_y(const float &y);

    /**
     * @brief Mutateur du coefficient d'agrandissement de l'affichage par la caméra, ne peut pas être négatif
     * @param zoom: float, nouveau coefficient d'agrandissement de l'affichage, multiplié par -1 si négatif
    */
    void set_zoom(const float &zoom);

    /**
     * @brief Accesseur de la position en x courante de la caméra
     * @return int, position en x courante
    */
    int &get_pos_x();

    /**
     * @brief Accesseur de la position en y courante de la caméra
     * @return int, position en y courante
    */
    int &get_pos_y();

    /**
     * @brief Accesseur du coefficient d'agrandissement courant
     * @return float, facteur d'agrandissement courant
    */
    float &get_zoom();

  private:
    int pos_x;
    int pos_y;
    float zoom;
};

#endif // !CAMERA_HEADER
