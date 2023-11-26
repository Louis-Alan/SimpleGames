#include "Player.hpp"
#include <iostream>
//
// Private functions
void Player::initTexture() {
    if (!this->texture.loadFromFile("../assets/ship.png")) {
        std::cout << "Error in texture load \n";
    }
}

void Player::initSprite() {
    this->sprite.setTexture(this->texture);

    // Resize the sprite
    this->sprite.setScale(0.1f, 0.1f);
}

// Constructor / Destructor
Player::Player() {
    this->movementSpeed = 10.f;

    this->initTexture();
    this->initSprite();
}

Player::~Player() {}

// Public functions
void Player::move(const float dirX, const float dirY) {
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::update() {}

void Player::render(sf::RenderTarget *target) { target->draw(this->sprite); }
