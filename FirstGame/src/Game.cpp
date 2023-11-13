#include "Game.hh"

#include "logger.h"

// Private Functions
void Game::initVariables() {
  this->window = nullptr;

  this->endGame = false;
  this->points = 0;
  this->health = 10;
  this->enemySpawnTimerMax = 10.f;
  this->enemySpawnTimer = this->enemySpawnTimerMax;
  this->maxEnemies = 10;
  this->mouseHeld = false;
}

void Game::initWindow() {
  this->videoMode.height = 600;
  this->videoMode.width = 800;
  this->window = new sf::RenderWindow(videoMode, "Game 1",
                                      sf::Style::Titlebar | sf::Style::Close);
  this->window->setFramerateLimit(60);
}

void Game::initFonts() {
  if (this->font.loadFromFile("fonts/Raleway.ttf")) {
    SM_ERROR("Failed in loading Font")
  }
}

void Game::initText() {
  this->uiText.setFont(this->font);
  this->uiText.setCharacterSize(16);
  this->uiText.setFillColor(sf::Color::White);
  this->uiText.setString("NONE");
}

void Game::initEnemies() {
  this->enemy.setPosition(10.f, 10.f);
  this->enemy.setSize(sf::Vector2f(100.f, 100.f));
  this->enemy.scale(sf::Vector2f(0.5f, 0.5f));
  this->enemy.setFillColor(sf::Color::Cyan);
}

// Constructor / Destructor
Game::Game() {
  this->initVariables();
  this->initWindow();
  this->initFonts();
  this->initText();
  this->initEnemies();
}

Game::~Game() {
  delete this->window;
}

// Accessors
const bool Game::isGameOver() const {
  return this->endGame;
}

const bool Game::running() const {
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

  // Randomize enemy type
  int type = rand() % 5;

  switch (type) {
    case 0:
      this->enemy.setFillColor(sf::Color::Magenta);
      this->enemy.setSize(sf::Vector2f(20.f, 20.f));
      break;
    case 1:
      this->enemy.setSize(sf::Vector2f(30.f, 30.f));
      this->enemy.setFillColor(sf::Color::Blue);
      break;
    case 3:
      this->enemy.setSize(sf::Vector2f(50.f, 50.f));
      this->enemy.setFillColor(sf::Color::Cyan);
      break;
    case 4:
      this->enemy.setSize(sf::Vector2f(70.f, 70.f));
      this->enemy.setFillColor(sf::Color::Red);
      break;
    case 5:
      this->enemy.setSize(sf::Vector2f(100.f, 100.f));
      this->enemy.setFillColor(sf::Color::Green);
      break;
    default:
      this->enemy.setSize(sf::Vector2f(100.f, 100.f));
      this->enemy.setFillColor(sf::Color::Yellow);
      break;
  }

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

void Game::updateText() {
  std::stringstream ss;
  ss << "Points: " << this->points << '\n' << "Health: " << this->health;
  this->uiText.setString(ss.str());
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
    this->enemies[i].move(0.f, 1.f);

    // If enemy is past bottom of the screen
    if (this->enemies[i].getPosition().y > this->window->getSize().y) {
      this->health -= 1;
      this->enemies.erase(this->enemies.begin() + i);
      SM_WARN("Health is %d", this->health);
    }
  }
  // Check if clicked upon
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    if (this->mouseHeld == false) {
      this->mouseHeld = true;
      bool deleted = false;
      for (size_t i = 0; i < this->enemies.size() && deleted == false; i++) {
        if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
          // Adding points
          if (this->enemies[i].getFillColor() == sf::Color::Magenta)
            this->points += 10;
          else if (this->enemies[i].getFillColor() == sf::Color::Blue)
            this->points += 7;
          else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
            this->points += 5;
          else if (this->enemies[i].getFillColor() == sf::Color::Red)
            this->points += 3;
          else if (this->enemies[i].getFillColor() == sf::Color::Green)
            this->points += 1;

          // Delete the enemy
          deleted = true;
          this->enemies.erase(this->enemies.begin() + i);
        }
      }
    }
  } else {
    this->mouseHeld = false;
  }
}

void Game::update() {
  this->pollEvents();

  if (this->endGame == false) {
    // Update Mouse Position
    this->updateMousePositions();

    this->updateText();

    this->updateEnemies();
  }

  // Endgame condition
  if (this->health <= 0) {
    this->endGame = true;
  }
}

void Game::renderText() {
  this->window->draw(this->uiText);
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
  this->renderText();

  this->window->display();
}
