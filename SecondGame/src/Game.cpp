// Copyright [2023] Alan Louis

#include "Game.hpp"
#include <sstream>

// Init functions
void Game::initVariables() {
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxBalls = 5;
    this->points = 0;
}

void Game::initWindow() {
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Game 2",
                                        sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initFont() { this->font.loadFromFile("../fonts/Raleway.ttf"); }

void Game::initText() {
    this->guiText.setFont(this->font);
    this->guiText.setFillColor(sf::Color::White);
    this->guiText.setCharacterSize(16);
    this->guiText.setString("TEST");
}

// Constructor / Destructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initFont();
    this->initText();
}

Game::~Game() { delete this->window; }

// Functions
const bool Game::running() const { return this->window->isOpen(); }

void Game::pollEvents() {
    while (this->window->pollEvent(this->sfmlEvent)) {
        switch (this->sfmlEvent.type) {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::spawnBalls() {
    // Timer
    if (this->spawnTimer < this->spawnTimerMax) {
        this->spawnTimer += 1.f;
    } else {
        if (this->balls.size() < this->maxBalls) {
            this->balls.push_back(
                Ball(*this->window, rand() % BallType::NROFTYPES));
            this->spawnTimer = 0.f;
        }
    }
}

void Game::updateCollision() {
    // check collision

    for (size_t i = 0; i < this->balls.size(); i++) {
        if (this->player.getShape().getGlobalBounds().intersects(
                this->balls[i].getShape().getGlobalBounds())) {
            switch (this->balls[i].getType()) {
            case BallType::DEFAULT:
                this->points++;
                break;
            case BallType::HEALING:
                this->player.gainHealth(1);
                break;
            case BallType::DAMAGING:
                this->player.takeDamage(1);
                break;
            }

            // Remove the ball
            this->balls.erase(this->balls.begin() + i);
        }
    }
}

void Game::updateText() {
    std::stringstream ss;

    ss << "Points: " << this->points << '\n'
       << "Health: " << this->player.getHp() << " / "
       << this->player.getHpMax();

    this->guiText.setString(ss.str());
}

void Game::renderGui() { this->window->draw(this->guiText); }

// public functions
void Game::update() {
    this->pollEvents();

    this->spawnBalls();

    this->player.update(this->window);
    this->updateCollision();

    this->updateText();
}

void Game::render() {
    this->window->clear();

    // Render Stuff
    this->player.render(this->window);

    for (auto i : this->balls) {
        i.render(this->window);
    }

    this->renderGui();

    // Display
    this->window->display();
}
