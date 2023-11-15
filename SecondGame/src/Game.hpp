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

  // Public Functions
  void update();
  void render();

 private:
  sf::VideoMode videoMode;
  sf::RenderWindow* window;
  bool endGame;
  sf::Event sfmlEvent;

  Player player;

  std::vector<Ball> balls;
  float spawnTimerMax;
  float spawnTimer;
  int maxBalls;

  // Init Functions
  void initVariables();
  void initWindow();

  // Functions
  void pollEvents();
  void spawnBalls();
};
