#include "Game.hh"

#include <ctime>
#include <vector>

#include "celeste_lib.h"

// Private Functions
void Game::initVariables() {
  this->window = nullptr;
  this->points = 0;
  this->enemySpawnTimerMax = 10.f;
  this->enemySpawnTimer = this->enemySpawnTimerMax;
  this->maxEnemies = 5;
}

void Game::initWindow() {
  this->videoMode.height = 600;
  this->videoMode.width = 800;
  this->window = new sf::RenderWindow(videoMode, "Game 1",
                                      sf::Style::Titlebar | sf::Style::Close);
  this->window->setFramerateLimit(60);
}

void Game::initEnemies() {
  this->enemy.setPosition(10.f, 10.f);
  this->enemy.setSize(sf::Vector2f(100.f, 100.f));
  this->enemy.scale(sf::Vector2f(0.5f, 0.5f));
  this->enemy.setFillColor(sf::Color::Cyan);
  this->enemy.setOutlineColor(sf::Color::Green);
  this->enemy.setOutlineThickness(1.f);
}

// Constructor / Destructor
Game::Game() {
  this->initVariables();
  this->initWindow();
  this->initEnemies();
}

Game::~Game() {
  delete this->window;
}

// Accessors
const bool Game::isWindowOpen() const {
  return this->window->isOpen();
}

// Public Functions

void Game::spawnEnemy() {
  /*
   *  @return void
   *
   *  Spawns enemies and sets their colors and positions
   *  -Sets a random position.
   *  -Sets a random color.
   *  -Adds enemy to the vector
   */

  this->enemy.setPosition(
      static_cast<float>(rand() % static_cast<int>(this->window->getSize().x -
                                                   this->enemy.getSize().x)),
      0.f);

  this->enemy.setFillColor(sf::Color::Green);

  // Spawn enemy
  this->enemies.push_back(this->enemy);
}

void Game::pollEvents() {
  while (this->window->pollEvent(this->ev)) {
    switch (this->ev.type) {
      case sf::Event::Closed:
        this->window->close();
        break;
      case sf::Event::KeyPressed:
        if (this->ev.key.code == sf::Keyboard::Escape) {
          this->window->close();
        }
        break;
    }
  }
}

void Game::updateMousePositions() {
  this->mousePosWindow = sf::Mouse::getPosition(*this->window);
  this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies() {
  /* @return void
   *
   * Updates the enemy spawn timer and spawns enemies
   * when the total amount of enemies is smaller than maximum.
   * Moves the enemies downwards.
   * Removes the enemies at edge of screen
   */

  // updating timer for enemy spawn
  if (this->enemies.size() < this->maxEnemies) {
    if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
      // spawn enemy reset timer
      this->spawnEnemy();
      this->enemySpawnTimer = 0.f;
    } else {
      this->enemySpawnTimer += 1.f;
    }
  }

  // Move and updating enemies
  for (int i = 0; i < this->enemies.size(); i++) {
    bool deleted = false;
    this->enemies[i].move(0.f, 1.f);

    // Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
        deleted = true;
      }
    }

    // If enemy is past bottom of the screen
    if (this->enemies[i].getPosition().y > this->window->getSize().y) {
      deleted = true;
    }

    if (deleted) {
      this->enemies.erase(this->enemies.begin() + i);
    }
  }
}

void Game::update() {
  this->pollEvents();

  // Update Mouse Position
  this->updateMousePositions();

  this->updateEnemies();
}

void Game::renderEnemies() {
  // Rendering all enemies
  for (auto& e : this->enemies) {
    this->window->draw(e);
  }
}

void Game::render() {
  /*
   *  - clear old frame
   *  - render objects
   *  - display frame in window
   */

  this->window->clear();

  // Draw game objects
  this->renderEnemies();

  this->window->display();
}
