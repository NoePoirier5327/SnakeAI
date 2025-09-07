#include "headers/game.hpp"
#include <cstdlib>

Game::Game(int height, int width)
{
  this->i_map = new Map(height, width);
  this->i_snake = new Snake(height, width);

  this->w_height = height; this->w_width = width;
  this->game_over = false;

  this->score = 0;
  this->start = time(nullptr);

  this->generate_new_apple();
}

Game::~Game()
{
  if (this->i_map != nullptr) delete this->i_map;
  if (this->i_snake != nullptr) delete this->i_snake;
}

void Game::run()
{
  this->update();
  this->display();
  this->handle_inputs();
}

bool Game::the_game_is_over() { return this->game_over; }

void Game::handle_inputs()
{
  int ch;
  switch (ch = getch())
  {
    case KEY_UP:
      //this->i_snake->move(0);
      this->direction = 0;
      break;

    case KEY_DOWN:
      //this->i_snake->move(1);
      this->direction = 1;
      break;

    case KEY_LEFT:
      //this->i_snake->move(2);
      this->direction = 2;
      break;

    case KEY_RIGHT:
      //this->i_snake->move(3);
      this->direction = 3;
      break;

    case 27: // ESCAPE
      this->game_over = true;
      break;

    default:
      break;
  }
}

void Game::generate_new_apple()
{
  // On parcours la carte pour trouver les tuiles non occupés par le serpent
  std::vector<Position> free_tiles;
  Position temp;

  for (int ligne = 1; ligne < this->w_height - 1; ligne++)
    for (int colonne = 1; colonne < this->w_width - 1; colonne++)
    {
      temp.x = ligne; temp.y = ligne;
      if (this->i_map->get_tile(temp) == 0) free_tiles.push_back(temp);
    }

  // On tire un nombre au hasard entre 0 et taille de tab - 1
  // et on attribue la position associé à la pomme
  this->p_apple = free_tiles[int_rng(0, (int)(free_tiles.size() - 1))];
}

void Game::update()
{
  // Move the snake
  this->i_snake->move(this->direction);

  std::vector<Position> snake = this->i_snake->get_pos();

  // On vérifie si le serpent est mort
  // On vérifie si la tête du serpent est dans le corp
  for (int i = 1; i < (int)(snake.size()); i++)
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
      this->game_over = true;
  
  // On vérifie si la tête est en dehors de la carte
  if ((snake[0].x >= 0 && snake[0].x < this->w_width && (snake[0].y == 0 || snake[0].y == this->w_height - 1)) ||
  (snake[0].y >= 0 && snake[0].y < this->w_height && (snake[0].x == 0 || snake[0].x == this->w_width - 1)))
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
    }

    // Update display
    this->i_map->set_blank();    
    this->i_map->set_tile(this->p_apple, 2); // On ajoute la pomme sur la carte
    this->i_map->set_tile(snake[0], 4); // On ajoute la tête du serpent sur la carte
    
    for (int i = 1; i < (int)(snake.size()); i++)
      this->i_map->set_tile(snake[i], 3);
  }
}

void Game::display()
{
  this->i_map->display();

  int col_location = this->w_width * 2;
  
  move(0, col_location);
  printw(" Game infos :");

  move(2, col_location);
  printw("  - Score : %d", this->score);

  move(3, col_location);
  printw("  - Time : %ds", (int) (time(nullptr) - this->start));
}
