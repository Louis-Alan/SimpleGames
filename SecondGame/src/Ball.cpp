#include "Ball.hpp"

void Ball::initShape(const sf::RenderWindow& window) {
  this->shape.setRadius(static_cast<float>((rand() % 10) + 10));
  sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
  this->shape.setFillColor(color);
  this->shape.setPosition(static_cast<float>(rand() % window.getSize().x),
                          static_cast<float>(rand() % window.getSize().y));

  sf::FloatRect bounds = this->shape.getGlobalBounds();
  if (bounds.left < 0.f) {
    this->shape.setPosition(0.f, bounds.top);
  } else if (bounds.left + bounds.width > window.getSize().x) {
    this->shape.setPosition(window.getSize().x - bounds.width, bounds.top);
  }
  if (bounds.top < 0.f) {
    this->shape.setPosition(bounds.left, 0.f);
  } else if (bounds.top + bounds.height > window.getSize().y) {
    this->shape.setPosition(bounds.left, window.getSize().y - bounds.height);
  }
}

Ball::Ball(const sf::RenderWindow& window) {
  this->initShape(window);
}

Ball::~Ball() {}

void Ball::update() {}

void Ball::render(sf::RenderTarget* target) {
  target->draw(this->shape);
}
