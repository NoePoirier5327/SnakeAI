/**
 * Fichier contenant l'implémentation des fonctions et classe du fichier map_engine.hpp
 * le 29/12/2025
 * par Noé Poirier
*/

#include "isometric_engine.hpp"

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

IsometricEngine::IsometricEngine()
{
  // On charge la caméra à la position 0 0 au zoom 1
  this->x_scale = 0;
  this->y_scale = 0;
  float zoom = 1.0;
  this->camera = new Camera(this->x_scale, this->y_scale, zoom);
}

IsometricEngine::~IsometricEngine()
{
  // On décharge la caméra courante si elle est utilisée
  if (this->camera != nullptr)
  {
    delete this->camera;
    this->camera = nullptr;
  }

  // On décharge la texture courant si elle est utilisée
  if (this->texture != nullptr)
  {
    SDL_DestroyTexture(this->texture);
    this->texture = nullptr;
  }
}

bool IsometricEngine::set_tile(const int &pos_x, const int &pos_y, const char &tile)
{
  // Si le point ne sort pas de la carte, on modifie la tuile et renvoie true
  if (pos_y >= 0 && pos_y < this->map.size())
  {
    if (pos_x >= 0 && pos_x < this->map[pos_y].size())
    {
      this->map[pos_y][pos_x] = tile;
      return true;
    }
  }

  // false sinon
  return false;
}

char IsometricEngine::get_tile(const int &pos_x, const int &pos_y)
{
  if (pos_y >= 0 && pos_y < this->map.size())
    if (pos_x >= 0 && pos_x < this->map[pos_y].size())
      return this->map[pos_y][pos_x];
  return '\n';
}

std::vector<std::vector<char>> &IsometricEngine::get_map()
{
  return this->map;
}

void IsometricEngine::display(SDL_Renderer *renderer)
{
  // On charge la config par défaut si aucune n'est chargé
  if (this->texture == nullptr)
  {
    std::cout << "Attention : aucune configuration n'est chargé, on charge la configuration d'exemple." << std::endl;
    this->load_exemple_config(renderer);
  }

  int pos_x;
  int pos_y;
  SDL_Rect rect;
  
  // Constantes de la GRILLE (le losange au sol)
  const float grid_w = this->x_scale * this->camera->get_zoom();
  const float grid_h = this->y_scale * this->camera->get_zoom();

  for (int line = 0; line < this->map.size(); ++line)
  {
    for (int column = 0; column < this->map[line].size(); ++column)
    {
      char tile_type = this->map[line][column];
      
      if (this->texture_shape.find(tile_type) != this->texture_shape.end())
      {
        // 1. On récupère la taille RÉELLE de la source (ex: 32x32 pour un bloc)
        SDL_Rect src_rect = this->texture_shape[tile_type];
        
        // 2. On calcule la taille de DESTINATION avec le zoom
        float dest_w = src_rect.w * this->camera->get_zoom();
        float dest_h = src_rect.h * this->camera->get_zoom();

        // 3. Calcul de la position de base sur la grille (le point d'ancrage)
        pos_x = (column - line) * (grid_w / 2);
        pos_y = (column + line) * (grid_h / 2);

        // 4. ALIGNEMENT : 
        // rect.x : On centre la texture horizontalement sur la cellule (si dest_w > grid_w)
        rect.x = pos_x + this->camera->get_pos_x() - (dest_w - grid_w) / 2;
        
        // rect.y : On aligne le BAS de la texture avec le BAS de la cellule de grille
        // On soustrait la hauteur réelle pour que l'objet "monte" depuis le sol
        rect.y = pos_y + this->camera->get_pos_y() - (dest_h - grid_h);
        
        rect.w = dest_w;
        rect.h = dest_h;

        SDL_RenderCopy(renderer, this->texture, &src_rect, &rect);
      }
    }
  }
}

Camera *IsometricEngine::get_camera()
{
  return this->camera;
}

bool IsometricEngine::load_map_from_file(const char *file_name)
{
  // On vide la carte courante
  while (this->map.empty() == false)
    this->map.pop_back();

  // On ouvre le fichier
  std::ifstream file(file_name);

  // S'il n'a pas été ouvert correctement, on renvoie false
  if (!file.is_open())
  {
    std::cerr << "Erreur : Impossible d'ouvrir la carte '" << file_name << "'." << std::endl;
    return false;
  }

  std::string line;
  int index_line = 0;

  // Tant que on peut lire dans le fichier, on construit la carte
  while (std::getline(file, line))
  {
    // Si on atteint le caractère de fin de ligne, on l'enlève pour éviter les bugs au traitement
    if (!line.empty() && line.back() == '\r')
      line.pop_back();

    // On ajoute un vecteur vide à la carte pour ensuite rajouter les caractères du fichier
    this->map.push_back({});

    // On ajoute les caracères de la ligne courante dans le fichier à la ligne correspondante dans la matrice
    for (size_t column = 0; column < line.size(); ++column)
      this->map[index_line].push_back(line[column]);

    // On incrémente l'index de la ligne
    index_line++;
  }

  // On ferme le fichier et renvoie true car l'opération s'est bien passée
  file.close();

  return true;
}

bool IsometricEngine::load_texture_from_file(const char *file_name, SDL_Renderer *renderer)
{
  // On charge la texture dans une surface SDL
  SDL_Surface *image = nullptr;
  image = IMG_Load(file_name);

  // On s'assure qu'elle a été chargé correctement, si non, on renvoies une erreur
  if (!image)
  {
    std::cerr << "Erreur : Impossible de charger la texture '" << file_name << "' en tant qu'image -> " << SDL_GetError() << std::endl;
    return false;
  }

  // On décharge l'ancienne texture avant d'appliquer la nouvelle
  if (this->texture != nullptr)
  {
    SDL_DestroyTexture(this->texture);
    this->texture = nullptr;
  }
  this->texture = SDL_CreateTextureFromSurface(renderer, image);

  // On décharge la surface occupée par la texture
  SDL_FreeSurface(image);

  // On renvoie true car l'opération s'est bien passée
  return true;
}

bool IsometricEngine::load_config_from_file(const char *file_name, SDL_Renderer *renderer)
{
  // On ouvre le fichier en paramètre
  std::ifstream file(file_name);
  std::string line;

  // On retourne une erreur si on n'arrive pas à ouvrir le fichier
  if (!file.is_open())
  {
    std::cerr << "Erreur : Impossible d'ouvrir le fichier de configuration '" << file_name << "'." << std::endl;
    return false;
  }

  // On lis la première ligne contenant la carte à charger
  std::getline(file, line);

  // On supprime le caractère de fin de ligne si besoin
  if (!line.empty() && line.back() == '\r')
    line.pop_back();

  // Si on se retrouve avec une ligne vide, on renvoie une erreur et charge la carte d'exemple
  if (line.empty())
  {
    std::cerr << "Erreur : Nom de la carte introuvable, on charge la configuration d'exemple à la place." << std::endl;

    this->load_exemple_config(renderer);

    file.close();
    return false;
  }

  // On charge la carte
  this->load_map_from_file(line.c_str());

  // On lis la seconde ligne contenant la texture à charger
  std::getline(file, line);

  // On supprime le caractère de fine de ligne si besoin
  if (!line.empty() && line.back() == '\r')
    line.pop_back();

  // Si on se retrouve avec une ligne vide, on renvoie une erreur et charge la texture d'exemple
  if (line.empty())
  {
    std::cerr << "Erreur : Nom de la texture introuvable, on charge la configuration d'exemple à la place." << std::endl;

    this->load_exemple_config(renderer);

    file.close();
    return false;
  }

  // On charge la texture
  this->load_texture_from_file(line.c_str(), renderer);

  // On vide le dictionnaire contenant les positions des tuiles sur la texture courante
  this->texture_shape.clear();

  // Si la carte est vide, on arrête de lire le fichier ici car il n'y a pas de tuile à lui appliquer
  if (this->map.empty())
  {
    file.close();
    return true;
  }

  std::string word;

  // On charge la ligne sur laquelle les paramètres de la caméra sont stockées
  std::getline(file, line);

  if (!line.empty() && line.back() == '\r')
    line.pop_back();

  // On lit les 3 premiers mots de la ligne
  std::istringstream stream(line);
  int k = 0;

  while (stream >> word && k != 3)
  {
    // On vérifie que les mots correspondent à des chaines transformable en entier ou flottant
    bool conforme = true; int ii = 0;
    while (conforme && ii < word.size())
    {
      if (!std::isfinite(word[ii]))
        conforme = false;
      ii++;
    }

    if (!conforme)
    {
      std::cerr << "Erreur : l'information '"<< word <<"' n'est pas conforme, on charge la configuration d'exemple à la place." << std::endl;
      this->load_exemple_config(renderer);

      file.close();
      return false;
    }

    // On récupère les valeurs et on les mets aux bons endroits
    switch (k)
    {
      case 0:
        this->camera->set_pos_x(std::stoi(word));
        break;

      case 1:
        this->camera->set_pos_y(std::stoi(word));
        break;

      case 2:
        this->camera->set_zoom(std::stof(word));
        break;

      default:
        break;
    }

    k++;
  }

  // Si la phrase fait moins de 3 mots, on retourne une erreur et charge la config d'exemple
  if (k < 3)
  {
    std::cerr << "Erreur : Toutes les informations sur la caméra ne sont pas disponibles, on charge la configuration d'exemple." << std::endl;

    this->load_exemple_config(renderer);

    file.close();
    return false;
  }

  // On charge l'échelle de référence pour l'affichage
  k = 0;
  std::getline(file, line);
  std::istringstream scale_stream(line);

  while (scale_stream >> word && k < 2)
  {
    // On vérifie que les mots de la phrase correspondent à des valeurs entiers convertibles
    bool conforme = true; int ii = 0;
    while (conforme && ii < word.size())
    {
      if (!std::isdigit(word[ii]))
        conforme = false;
      ii++;
    }

    if (!conforme)
    {
      std::cerr << "Erreur : l'information '" << word << "' n'est pas conforme, on charge la configuration d'exemple." << std::endl;

      this->load_exemple_config(renderer);

      file.close();
      return false;
    }

    // On récupère les valeurs
    switch (k)
    {
      case 0:
        this->x_scale = std::stoi(word);
        break;

      case 1:
        this->y_scale = std::stoi(word);
        break;

      default:
        break;
    }

    k++;
  }

  // Si la phrase fait moins de 2 mots, on retourne une erreur et charge la config d'exemple
  if (k < 2)
  {
    std::cerr << "Erreur : Toutes les informations sur l'échelle ne sont pas disponibles, on charge la configuration d'exemple." << std::endl;

    this->load_exemple_config(renderer);

    file.close();
    return false;
  }

  int line_index = 5;

  // Sinon, on lis la suite du fichier pour récupérer les tuiles contenuent dans la carte
  while (std::getline(file, line))
  {
    // On suprimme le caractère de fin de ligne de la ligne courante
    if (!line.empty() && line.back() == '\r')
      line.pop_back();

    // On lis les mots composant la ligne courante
    std::istringstream line_stream(line);
    int i = 0; // index permettant de savoir à quel mot on est
    char key;
    SDL_Rect tile;

    while (line_stream >> word && i != 5)
    {
      // Si le premier mot de la phrase a une taille supérieur à 1, on retourne une erreur
      if (word.size() != 1 && i == 0)
      {
        std::cerr << "Erreur : le caractère d'identification n'est pas valide, on charge la configuration d'exemple." << std::endl;

        this->load_exemple_config(renderer);

        file.close();
        return false;
      }

      // On vérifie que le mot courant est composée de caractère transformable en entier
      if (i != 0)
      {
        bool conforme = true;
        int j = 0;

        while (conforme && j < word.size())
        {
          if (!std::isdigit(word[j]))
            conforme = false;
          j++;
        }

        // Si le caractères ne sont pas convertibles, on retourne une erreur
        if (!conforme)
        {
          std::cerr << "Erreur ligne " << line_index << " mot " << i << " : le format de donnée n'est pas correct, on charge la configuration d'exemple." << std::endl;

          this->load_exemple_config(renderer);

          file.close();
          return false;
        }
      }

      // On traite le mot en fonction de sa position dans la phrase
      switch (i)
      {
        // En première position, on a la clé
        case 0:
          key = word[0];
          break;

        // Ensuite, on a la position en x de la tuile cible
        case 1:
          tile.x = std::stoi(word);
          break;

        // Après, on a la position y
        case 2:
          tile.y = std::stoi(word);
          break;

        // Puis on a la largeur de la tuile
        case 3:
          tile.w = std::stoi(word);
          break;

        // Enfin on a la hauteur de la tuile
        case 4:
          tile.h = std::stoi(word);
          break;

        default:
          break;
      }

      i++;
    }

    // On sait que si i est inférieur à 5, le fichier n'est pas conforme
    if (i < 5)
    {
      std::cerr << "Erreur ligne " << line_index << " : information manquante concernant la texture, on charge la configuration d'exemple à la place." << std::endl;

      this->load_exemple_config(renderer);
      
      file.close();
      return false;
    }

    // On ajoute la nouvelle tuile aux textures accessibles par le programme
    this->texture_shape[key] = tile;

    // On incrémente l'index de ligne
    line_index++;
  }

  // On ferme le fichier courant
  file.close();

  // On vérifie que les tuiles chargé dans la carte ont bien une texture accessible
  // le caractère espace n'a pas de texture et n'est pas pris en compte par l'algorithme
  for (int i = 0; i < this->map.size(); ++i)
  {
    for (int j = 0; j < this->map[i].size(); ++j)
    {
      if (this->map[i][j] != ' ')
      {
        if (this->texture_shape.find(this->map[i][j]) == this->texture_shape.end())
        {
         std::cerr << "Erreur : la carte n'est pas conforme aux textures fournient, on charge la configuration par défaut." << std::endl;

          this->load_exemple_config(renderer);

          return false;
        }
      }
    }
  }

  return true;
}

void IsometricEngine::load_exemple_config(SDL_Renderer *renderer)
{
  this->load_config_from_file("res/exemple/config.txt", renderer);
}

void IsometricEngine::set_as_new_map(const std::vector<std::vector<char>> &map)
{
  this->map = map;
}

void IsometricEngine::set_scale(const int &x_scale, const int &y_scale)
{
  this->x_scale = x_scale;
  this->y_scale = y_scale;
}

void IsometricEngine::set_x_scale(const int &x_scale)
{
  this->x_scale = x_scale;
}

void IsometricEngine::set_y_scale(const int &y_scale)
{
  this->y_scale = y_scale;
}

int &IsometricEngine::get_x_scale()
{
  return this->x_scale;
}

int &IsometricEngine::get_y_scale()
{
  return this->y_scale;
}

bool IsometricEngine::set_as_new_texture(SDL_Texture *texture)
{
  if (texture == nullptr)
  {
    std::cerr << "Erreur : Impossible d'attribuer une texture non définie à la carte courante." << std::endl;
    return false;
  }

  // On déalloue la texture courante
  if (this->texture != nullptr)
  {
    SDL_DestroyTexture(this->texture);
    this->texture = nullptr;
  }

  // On attribue la texture en paramètre
  this->texture = texture;
  return true;
}

void IsometricEngine::set_as_new_texture_shape(const std::map<char, SDL_Rect> &shape)
{
  this->texture_shape = shape;
}

void IsometricEngine::add_texture_shape(const char &key, const SDL_Rect &shape)
{
  this->texture_shape[key] = shape;
}
