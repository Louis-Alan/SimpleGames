// Copyright [2023] Alan Louis
#pragma once

#include <ctime>
#include <vector>

#include "Ball.hpp"
#include "Player.hpp"

class Game {
 public:
    Game();
    ~Game();

    // Accessors
    const bool running() const;
    const bool &getEndGame() const;

    // Public Functions
    void update();
    void render();

 private:
    sf::VideoMode videoMode;
    sf::RenderWindow *window;
    bool endGame;
    sf::Event sfmlEvent;

    sf::Font font;
    sf::Text guiText;
    sf::Text endGameText;

    Player player;
    int points;

    std::vector<Ball> balls;
    float spawnTimerMax;
    float spawnTimer;
    int maxBalls;

    // Init Functions
    void initVariables();
    void initWindow();
    void initFont();
    void initText();

    // Functions
    void pollEvents();
    void spawnBalls();
    const int randBallType() const;

    void updatePlayer();
    void updateCollision();
    void updateText();

    void renderGui();
    void renderEndGame();
};
