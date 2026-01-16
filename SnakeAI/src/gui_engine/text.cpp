/**
 * Fichier contenant l'implémentation de la classe Text
 * le 3/01/2026
 * par Noé Poirier
*/

#include "text.hpp"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

Text::Text(const std::string &text , const int &pos_x, const int &pos_y, const std::string &font_name, const int &font_size, const SDL_Color &color, SDL_Renderer *renderer)
{
  this->text_color = color;

  this->rect.x = pos_x;
  this->rect.y = pos_y;
  this->rect.w = 0;
  this->rect.h = 0;

  // On définie les pointeurs de l'instance courante comme des pointeurs nulles
  this->font = nullptr;
  this->texture = nullptr;
  this->surface = nullptr;

  // Si on arrive à charger la police de caractère, on charge le texte
  if (this->load_font(font_name, font_size))
    this->set_text(text, renderer);
}

Text::~Text()
{
  if (this->font != nullptr)
  {
    TTF_CloseFont(this->font);
    this->font = nullptr;
  }

  if (this->surface != nullptr)
  {
    SDL_FreeSurface(this->surface);
    this->surface = nullptr;
  }

  if (this->texture != nullptr)
  {
    SDL_DestroyTexture(this->texture);
    this->texture = nullptr;
  }
}

bool Text::display(SDL_Renderer *renderer)
{
  // Si les éléments qui sont censé êtr chargés lors de l'affichage ne le sont pas
  // On renvoie une erreur
  if (this->font == nullptr)
  {
    std::cerr << "Erreur : Aucune police de caractère n'est chargé." << std::endl;
    return false;
  }

  if (this->surface == nullptr)
  {
    std::cerr << "Erreur : Aucune surface n'est chargé pour créer le texte." << std::endl;
    return false;
  }

  if (this->texture == nullptr)
  {
    std::cerr << "Erreur : Aucun texte n'est chargé." << std::endl;
    return false;
  }

  //SDL_QueryTexture(this->texture, nullptr, nullptr, &this->rect.w, &this->rect.h);
  SDL_RenderCopy(renderer, this->texture, nullptr, &this->rect);
  return true;
}

bool Text::load_font(const std::string &font_name, const int &font_size)
{
  // S'il y a déjà une police de chargé, on la décharge avant d'en chargé une nouvelle
  if (this->font != nullptr)
  {
    TTF_CloseFont(this->font);
    this->font = nullptr;
  }

  this->font = TTF_OpenFont(font_name.c_str(), font_size);
  this->font_size = font_size;
  return true;
}

std::string &Text::get_font_name()
{
  return this->font_name;
}

int &Text::get_font_size()
{
  return this->font_size;
}

bool Text::set_text(const std::string &text, SDL_Renderer *renderer)
{
  // Si aucune police n'est chargé, on renvoie une erreur
  if (this->font == nullptr)
  {
    std::cerr << "Erreur : Avant de chargé du texte, il faut chargé une police de caractère." << std::endl;
    return false;
  }

  this->text = text;

  // On décharge l'ancienne surface pour en créer une nouvelle avec le nouveau texte
  if (this->surface != nullptr)
  {
    SDL_FreeSurface(this->surface);
    this->surface = nullptr;
  }

  if (this->texture != nullptr)
  {
    SDL_DestroyTexture(this->texture);
    this->texture = nullptr;
  }

  this->surface = TTF_RenderText_Blended(this->font, this->text.c_str(), this->text_color);
  this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);

  SDL_QueryTexture(this->texture, nullptr, nullptr, &this->rect.w, &this->rect.h);

  return true;
}

std::string &Text::get_text()
{
  return this->text;
}

void Text::set_text_color(const SDL_Color &color)
{
  this->text_color = color;
}

SDL_Color &Text::get_text_color()
{
  return this->text_color;
}

void Text::set_pos(const int &pos_x, const int &pos_y)
{
  this->rect.x = pos_x;
  this->rect.y = pos_y;
}

void Text::set_pos_x(const int &pos_x)
{
  this->rect.x = pos_x;
}

void Text::set_pos_y(const int &pos_y)
{
  this->rect.y = pos_y;
}

int &Text::get_pos_x()
{
  return this->rect.x;
}

int &Text::get_pos_y()
{
  return this->rect.y;
}
