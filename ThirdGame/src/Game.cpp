#include "Game.hpp"
#include <iostream>

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "SpaceShooter",
                                        sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initPlayer() { this->player = new Player(); }

void Game::initTextures() {
    this->bulletTexture = new sf::Texture();
    if (!this->bulletTexture->loadFromFile("../assets/bullet.png")) {
        std::cout << "Error in loading bullet";
    }
}

// Constructor / Destructor
Game::Game() {
    this->window = nullptr;
    this->initWindow();
    this->initTextures();
    this->initPlayer();
}

Game::~Game() {
    delete this->window;
    delete this->player;

    for (auto *i : this->bullets) {
        delete i;
    }
}

// Functions
void Game::run() {
    while (this->window->isOpen()) {
        this->update();
        this->render();
    }
}

void Game::updatePollEvents() {
    sf::Event e;
    while (this->window->pollEvent(e)) {
        if (e.Event::type == sf::Event::Closed) {
            this->window->close();
        }
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape) {
            this->window->close();
        }
    }
}

void Game::updateInput() {
    // Move Player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->player->move(-1.f, 0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->player->move(1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->player->move(0.f, -1.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->player->move(0.f, 1.f);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->bullets.push_back(new Bullet(this->bulletTexture, 0, 0, 0, 0, 0));
    }
}

void Game::updateBullets() {
    for (auto *bullet : this->bullets) {
        bullet->update();
    }
}

void Game::update() {
    this->updatePollEvents();

    this->updateInput();
    this->updateBullets();
}

void Game::render() {
    this->window->clear();

    // Draw everything
    this->player->render(this->window);

    for (auto *bullet : this->bullets) {
        bullet->render(this->window);
    }

    this->window->display();
}
