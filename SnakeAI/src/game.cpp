#include "game.hpp"

#include <iostream>
#include <cstdlib>

Game::Game(const int &map_width, const int &map_height, SDL_Renderer *renderer)
{
  // On charge la carte et le serpent
  this->i_map = new IsometricEngine();
  this->i_snake = new Snake();

  this->game_over = false;
  this->score = 0;

  // On charge les textures
  this->i_map->load_texture_from_file("../res/isometric_snake.png", renderer);
  this->i_map->add_texture_shape('.', {0, 0, 32, 16});
  this->i_map->add_texture_shape('A', {0, 32, 32, 32});
  this->i_map->add_texture_shape('S', {32, 0, 32, 24});

  // On charge la configuration de la caméra
  this->i_map->get_camera()->set_pos(200, 50);
  this->i_map->get_camera()->set_zoom(2);

  // On charge l'échelle de rendue des textures isométriques
  this->i_map->set_scale(32, 16);

  // On charge la carte vide
  this->empty_map.reserve(map_height);
  std::vector<char> line;
  line.reserve(map_width);

  for (int i = 0; i < map_width; ++i)
    line.push_back('.');

  for (int i = 0; i < map_height; ++i)
    this->empty_map.push_back(line);

  this->i_map->set_as_new_map(this->empty_map);

  // On ajoute le serpent à la carte, il est de taille 1 au début
  // On suppose qu'il est forcément dans l'ensemble de définition de la carte.
  Position pos = this->i_snake->get_pos().front();
  this->i_map->set_tile(pos.x, pos.y, 'S');

  // On génère une nouvelle pomme pour le jeu
  this->generate_new_apple();
  this->i_map->set_tile(this->p_apple.x, this->p_apple.y, 'A');
}

Game::~Game()
{
  if (this->i_map != nullptr) delete this->i_map;
  if (this->i_snake != nullptr) delete this->i_snake;
}

void Game::handle_inputs(const Direction &direction)
{
  this->direction = direction;

  Position camera_pos, scale;
  camera_pos.x = this->i_map->get_camera()->get_pos_x();
  camera_pos.y = this->i_map->get_camera()->get_pos_y();
  scale.x = this->i_map->get_x_scale();
  scale.y = this->i_map->get_y_scale();
  
  switch (this->direction)
  {
    case haut:
      this->i_map->get_camera()->set_pos(camera_pos.x - scale.x, camera_pos.y + scale.y);
      break;

    case bas:
      this->i_map->get_camera()->set_pos(camera_pos.x + scale.x, camera_pos.y - scale.y);
      break;

    case gauche:
      this->i_map->get_camera()->set_pos(camera_pos.x + scale.x, camera_pos.y + scale.y);
      break;

    case droite:
      this->i_map->get_camera()->set_pos(camera_pos.x - scale.x, camera_pos.y - scale.y);
      break;
  }
}

void Game::generate_new_apple()
{
  // On parcourt la carte pour trouver les tuiles non occupés par le serpent
  std::vector<Position> free_tiles;

  int n = 0;

  for (int ligne = 1; ligne < MAP_HEIGHT - 1; ligne++)
    for (int colonne = 1; colonne < MAP_WIDTH - 1; colonne++)
    {
      Position temp = {colonne, ligne};
      if (this->i_map->get_tile(temp.x, temp.y) == '.')
      {
        free_tiles.push_back(temp);
        n++;
      }
    }

  // S'il n'y a aucune case pour une nouvelle pomme, on arrête le jeu
  if (free_tiles.empty())
  {
    this->game_over = true;
    return;
  }
  // On tire un nombre au hasard entre 0 et taille de tab - 1
  // et on attribue la position associé à la pomme
  this->p_apple = free_tiles[rand() % n];
}

void Game::update()
{
  this->apple_eaten = false;

  // On le fait se déplacer selon sa dernière direction enregistré
  this->i_snake->move(this->direction);

  std::vector<Position> snake = this->i_snake->get_pos();
  
  //std::cout << (snake.empty() == true ? "true" : "false") << std::endl;

  // On vérifie si le serpent est mort
  // On vérifie si la tête du serpent est dans le corp
  for (size_t i = 1; i < snake.size(); ++i)
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
      this->game_over = true;
  
  // On vérifie si la tête est en dehors de la carte
  if (snake[0].x < 0 || snake[0].x >= MAP_WIDTH || snake[0].y < 0 || snake[0].y >= MAP_HEIGHT)
    this->game_over = true;
  
  // Si le serpent n'est pas mort, on peut continuer le jeu
  if (this->game_over == false)
  {
    // Si le serpent mange une pomme, on incrémente son score et en génère une nouvelle
    if (this->i_map->get_tile(snake[0].x, snake[0].y) == 2)
    {
      this->i_snake->eat_apple(); // le serpent mange la pomme
      this->i_map->set_tile(this->p_apple.x, this->p_apple.y, '.'); // on la supprime de la carte

      this->generate_new_apple(); // On en génère une nouvelle
      this->score++; // On incrémente le score
      this->apple_eaten = true; // On informe qu'on a mangé une pomme
      this->i_map->set_tile(this->p_apple.x, this->p_apple.y, 'A'); // On ajoute la nouvelle pomme à la carte
    }

    // On met à jour la carte
    this->i_map->set_as_new_map(this->empty_map);
    this->i_map->set_tile(this->p_apple.x, this->p_apple.y, 'A'); // On ajoute la pomme sur la carte
    
    // On ajoute le serpent sur la carte
    for (size_t i = 0; i < snake.size(); ++i)
      this->i_map->set_tile(snake[i].x, snake[i].y, 'S');
  }
}

void Game::display(SDL_Renderer* renderer)
{
  this->i_map->display(renderer);
}

bool Game::the_snake_ate_an_apple() 
{
  return this->apple_eaten; 
}

int& Game::get_score() { return this->score; }

std::vector<double> Game::get_game_state()
{
  std::vector<double> game_state; game_state.reserve(77);

  Position head = this->i_snake->get_pos()[0];
  
  // On récupère le pov du serpent 5x5
  for (int l = -2; l <= 2; l++)
    for (int c = -2; c <= 2; c++)
    {
      Position p = {head.x + c, head.y + l};

      char tile = this->i_map->get_tile(p.x, p.y);
      game_state.push_back(tile == '.' ? 1.0 : 0.0);
      game_state.push_back(tile == 'A' ? 1.0 : 0.0);
      game_state.push_back(tile == 'S' ? 1.0 : 0.0);
    }

  // On récupère la distance avec la pomme (normalisé entre -1 et 1)
  game_state.push_back((this->p_apple.x - head.x) / static_cast<double>(MAP_WIDTH));
  game_state.push_back((this->p_apple.y - head.y) / static_cast<double>(MAP_HEIGHT));

  /*
  // On traite les données pour qu'elles soient comprises entre 0 et 1
  double max_elm = *std::max_element(game_state.begin(), game_state.end());
  
  if (max_elm != 0)
    for (size_t i = 0; i < game_state.size(); i++)
      game_state[i] /= max_elm;
  */

  return game_state;
}
