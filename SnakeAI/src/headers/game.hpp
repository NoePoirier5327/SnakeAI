#pragma once

#include "map.hpp"
#include "snake.hpp"
#include "apple.hpp"

class Game
{
  public:
    Game(int height, int width);
    ~Game();

    void run();

    bool the_game_is_over();

  private:
    void handle_inputs();
    void update();
    void display();

    bool the_snake_is_dead();

    int w_height;
    int w_width;

    bool game_over;
    
    int direction;

    Snake *i_snake;
    Map *i_map;
    Apple *i_apple;
};
