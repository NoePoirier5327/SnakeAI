#include "headers/game.hpp"

Game::Game(int height, int width)
{
  this->i_map = new Map(height, width);
  this->i_apple = new Apple(height, width);
  this->i_snake = new Snake(height, width);

  this->w_height = height; this->w_width = width;
  this->game_over = false;

  this->score = 0;
  this->start = time(nullptr);
}

Game::~Game()
{
  if (this->i_map != nullptr) delete this->i_map;
  if (this->i_apple != nullptr) delete this->i_apple;
  if (this->i_snake != nullptr) delete this->i_snake;
}

void Game::run()
{
  this->update();
  this->display();
  this->handle_inputs();
}

bool Game::the_game_is_over()
{
  if (!this->game_over)
    this->game_over = this->the_snake_is_dead();
  return this->game_over;
}

bool Game::the_snake_is_dead()
{
  // On vérifie si la tête est en dehors de l'écran
  std::vector<Position> snake = this->i_snake->get_pos();
  bool is_dead = false;

  if (snake[0].x == 0 && snake[0].x == this->w_width-1 && snake[0].y == 0 && snake[0].y == this->w_height-1)
    is_dead = true;
  
  int i = 1;
  while (i != (int)(snake.size()) && !is_dead)
  {
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) is_dead = true;
    i++;
  }

  return is_dead;
}

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

void Game::update()
{
  // Move the snake
  this->i_snake->move(this->direction);

  std::vector<Position> snake = this->i_snake->get_pos();
  
  // Eat apple
  if (this->i_map->get_tile(snake[0]) == 2)
  {
    this->i_snake->eat_apple();
    delete this->i_apple;
    this->i_apple = new Apple(this->w_height, this->w_width);
    this->score++; // On incrémente le score lorsqu'on mange une pomme
  }

  // Update display
  this->i_map->set_blank();
  this->i_map->set_tile(this->i_apple->get_pos(), 2);
  
  this->i_map->set_tile(snake[0], 4);

  for (int i = 1; i < (int)(snake.size()); i++)
    this->i_map->set_tile(snake[i], 3);
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
