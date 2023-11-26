#pragma once

#include "Player.hpp"

class Game {
 public:
    Game();
    ~Game();

    // Functions
    void run();
    void update();
    void render();

 private:
    sf::RenderWindow *window;

    Player *player;

    // Private Functions
    void initWindow();
    void initPlayer();
};
