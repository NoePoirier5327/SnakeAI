/**
 * Fichier contenant l'implémentation de la caméra dans le fichier camera.hpp
 * le 29/12/2025
 * par Noé Poirier
*/

#include "camera.hpp"

Camera::Camera(const int &pos_x, const int &pos_y, float &zoom)
{
  this->pos_x = pos_x;
  this->pos_y = pos_y;
  this->zoom = zoom;
}

void Camera::set_pos(const int &pos_x, const int &pos_y)
{
  this->pos_x = pos_x;
  this->pos_y = pos_y;
}

void Camera::set_pos_x(const float &x)
{
  this->pos_x = x;
}

void Camera::set_pos_y(const float &y)
{
  this->pos_y = y;
}

void Camera::set_zoom(const float &zoom)
{
  if (zoom <= 0) this->zoom = -1 * zoom; // Si le zoom est négatif, on le rend positif et l'attibue
  else this->zoom = zoom; // Sinon on l'attribue simplement
}

int &Camera::get_pos_x()
{
  return this->pos_x;
}

int &Camera::get_pos_y()
{
  return this->pos_y;
}

float &Camera::get_zoom()
{
  return this->zoom;
}
