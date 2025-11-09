#include "headers/game.hpp"

Game::Game()
{
  this->i_map = new IsometricMap();
  this->i_snake = new Snake();

  this->game_over = false;
  
  this->kill_timer = 0;
  this->score = 0;
  this->start = time(nullptr);

  this->generate_new_apple();
}

Game::~Game()
{
  if (this->i_map != nullptr) delete this->i_map;
  if (this->i_snake != nullptr) delete this->i_snake;
}

void Game::handle_inputs(int direction)
{
  this->direction = direction;
  /*
  switch (event.key.keysym.sym)
  {
    case SDLK_UP:
      this->direction = 0;
      break;

    case SDLK_DOWN:
      this->direction = 1;
      break;

    case SDLK_LEFT:
      //this->direction = 2;
      this->direction = 3;
      break;

    case SDLK_RIGHT:
      //this->direction = 3;
      this->direction = 2;
      break;

    case SDLK_ESCAPE:
      this->game_over = true;
      break;

    default:
      break;
  }*/
}

void Game::generate_new_apple()
{
  // On parcours la carte pour trouver les tuiles non occupés par le serpent
  std::vector<Position> free_tiles;
  Position temp;

  for (int ligne = 1; ligne < MAP_HEIGHT - 1; ligne++)
    for (int colonne = 1; colonne < MAP_WIDTH - 1; colonne++)
    {
      temp.x = colonne; temp.y = ligne;
      if (this->i_map->get_tile(temp) == 0) free_tiles.push_back(temp);
    }

  // On tire un nombre au hasard entre 0 et taille de tab - 1
  // et on attribue la position associé à la pomme
  this->p_apple = free_tiles[int_rng(0, (int)(free_tiles.size() - 1))];
}

void Game::update()
{
  // Si le serpent n'a pas mangé de pomme depuis N itérations de la boucle de jeu, on met fin à la partie
  if (this->kill_timer > KILL_TIMER_LIMIT) 
  {
    this->game_over = true;
    return;
  }
  
  // Sinon, on incrémente son timer et on continue la fonction
  this->kill_timer ++;

  this->apple_eaten = false;

  // Move the snake
  this->i_snake->move(this->direction);

  std::vector<Position> snake = this->i_snake->get_pos();
  //std::cout << (snake.empty() == true ? "true" : "false") << std::endl;

  // On vérifie si le serpent est mort
  // On vérifie si la tête du serpent est dans le corp
  for (int i = 1; i < (int)(snake.size()); i++)
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
      this->game_over = true;
  
  // On vérifie si la tête est en dehors de la carte
  if (snake[0].x < 0 || snake[0].x >= MAP_WIDTH || snake[0].y < 0 || snake[0].y >= MAP_HEIGHT)
    this->game_over = true;
  
  // Si le serpent n'est pas mort, on peut continuer le jeu
  if (this->game_over == false)
  {
    // Eat apple
    if (this->i_map->get_tile(snake[0]) == 2)
    {
      this->i_snake->eat_apple();
      this->generate_new_apple();
      this->score++; // On incrémente le score lorsqu'on mange une pomme
      this->apple_eaten = true;
    }

    // Update display
    this->i_map->set_blank();    
    this->i_map->modify(this->p_apple, t_apple); // On ajoute la pomme sur la carte
    
    // On ajoute le serpent sur la carte
    for (int i = 0; i < (int)(snake.size()); i++)
      this->i_map->modify(snake[i], t_snake);
  }
}

void Game::display(SDL_Renderer* renderer, SDL_Texture* tileset) { this->i_map->display(renderer, tileset); }

bool Game::the_snake_ate_an_apple() 
{
  // Si le serpent a mangé une pomme, on réinitialise son temps de vie
  if (this->apple_eaten) this->kill_timer = 0;
  return this->apple_eaten; 
}

int Game::get_score() { return this->score; }

std::vector<double> Game::get_game_state()
{
  std::vector<double> game_state; game_state.reserve(77);

  Position head = this->i_snake->get_pos()[0]; 
  Position p;
  TileType tile;
  
  // On récupère le pov du serpent 5x5
  for (int l = -2; l <= 2; l++)
    for (int c = -2; c <= 2; c++)
    {
      p = {head.x + c, head.y + l};

      tile = this->i_map->get_tile(p);
      game_state.push_back(tile == t_floor ? 1.0 : 0.0);
      game_state.push_back(tile == t_apple ? 1.0 : 0.0);
      game_state.push_back(tile == t_snake ? 1.0 : 0.0);
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
