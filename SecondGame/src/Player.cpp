#include "Player.hpp"

void Player::initVariables() {
  this->movementSpeed = 5.f;
}

void Player::initShape() {
  this->shape.setFillColor(sf::Color::Green);
  this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(float x, float y) {
  this->shape.setPosition(x, y);

  this->initVariables();
  this->initShape();
}

Player::~Player() {}

void Player::updateInput() {
  // Keyboard input
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    this->shape.move(-this->movementSpeed, 0.f);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    this->shape.move(this->movementSpeed, 0.f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    this->shape.move(0.f, -this->movementSpeed);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    this->shape.move(0.f, this->movementSpeed);
  }
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target) {
  sf::FloatRect bounds = this->shape.getGlobalBounds();

  if (bounds.left <= 0.f) {
    this->shape.setPosition(0.f, bounds.top);
  } else if (bounds.left + bounds.width >= target->getSize().x) {
    this->shape.setPosition(target->getSize().x - bounds.width, bounds.top);
  }

  bounds = this->shape.getGlobalBounds();
  if (bounds.top <= 0.f) {
    this->shape.setPosition(bounds.left, 0.f);
  } else if (bounds.top + bounds.height >= target->getSize().y) {
    this->shape.setPosition(bounds.left, target->getSize().y - bounds.height);
  }
}

void Player::update(const sf::RenderTarget* target) {
  this->updateInput();

  // Window bounds collision
  this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget* target) {
  target->draw(this->shape);
}
