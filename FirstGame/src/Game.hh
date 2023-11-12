#ifndef SRC_GAME_H
#define SRC_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

class Game {
 private:
  // Variables
  sf::RenderWindow* window;
  sf::VideoMode videoMode;
  sf::Event ev;

  // Mouse positions
  sf::Vector2i mousePosWindow;
  sf::Vector2f mousePosView;

  // Game logic
  bool endGame;
  unsigned points;
  int health;
  float enemySpawnTimer;
  float enemySpawnTimerMax;
  int maxEnemies;
  bool mouseHeld;

  // Game objects
  std::vector<sf::RectangleShape> enemies;
  sf::RectangleShape enemy;

  // Private functions
  void initVariables();
  void initWindow();
  void initEnemies();

 public:
  Game();
  ~Game();

  // Accessors
  const bool running() const;
  const bool isGameOver() const;

  // Functions
  void spawnEnemy();

  void updateMousePositions();
  void pollEvents();
  void updateEnemies();
  void update();

  void renderEnemies();
  void render();
};

#endif  // SRC_GAME_H
