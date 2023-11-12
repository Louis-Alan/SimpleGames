#ifndef SRC_GAME_H
#define SRC_GAME_H

#include <ctime>
#include <sstream>
#include <vector>

#include <SFML/Graphics.hpp>

class Game {
 private:
  // Variables
  sf::RenderWindow* window;
  sf::VideoMode videoMode;
  sf::Event ev;

  // Mouse positions
  sf::Vector2i mousePosWindow;
  sf::Vector2f mousePosView;

  // Resources
  sf::Font font;

  // Text
  sf::Text uiText;

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
  void initFonts();
  void initText();
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
  void updateText();
  void updateEnemies();
  void update();

  void renderText();
  void renderEnemies();
  void render();
};

#endif  // SRC_GAME_H
