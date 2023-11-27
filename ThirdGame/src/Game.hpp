#pragma once

#include <map>
#include <string>
#include <vector>

#include "Bullet.hpp"
#include "Player.hpp"

class Game {
 public:
    Game();
    ~Game();

    // Functions
    void run();

    void updatePollEvents();
    void updateInput();
    void updateBullets();
    void update();

    void render();

 private:
    // Window
    sf::RenderWindow *window;

    // Resources
    sf::Texture *bulletTexture;
    std::vector<Bullet *> bullets;

    // Player
    Player *player;

    // Private Functions
    void initWindow();
    void initPlayer();
    void initTextures();
};
