#include "Ball.hpp"

void Ball::initShape(const sf::RenderWindow &window) {
    this->shape.setRadius(static_cast<float>((rand() % 10) + 10));
    sf::Color color;
    switch (this->type) {
    case BallType::DEFAULT:
        color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
        break;
    case BallType::HEALING:
        color = sf::Color::Green;
        this->shape.setOutlineThickness(2.f);
        this->shape.setOutlineColor(sf::Color::White);
        break;
    case BallType::DAMAGING:
        color = sf::Color::Red;
        this->shape.setOutlineThickness(2.f);
        this->shape.setOutlineColor(sf::Color::Yellow);
        break;
    }

    this->shape.setFillColor(color);
    this->shape.setPosition(
        static_cast<float>(rand() % window.getSize().x -
                           this->shape.getGlobalBounds().width),
        static_cast<float>(rand() % window.getSize().y -
                           this->shape.getGlobalBounds().height));

    sf::FloatRect bounds = this->shape.getGlobalBounds();
    if (bounds.left < 0.f) {
        this->shape.setPosition(0.f, bounds.top);
    } else if (bounds.left + bounds.width > window.getSize().x) {
        this->shape.setPosition(window.getSize().x - bounds.width, bounds.top);
    }
    if (bounds.top < 0.f) {
        this->shape.setPosition(bounds.left, 0.f);
    } else if (bounds.top + bounds.height > window.getSize().y) {
        this->shape.setPosition(bounds.left,
                                window.getSize().y - bounds.height);
    }
}

Ball::Ball(const sf::RenderWindow &window, int type) : type(type) {
    this->initShape(window);
}

Ball::~Ball() {}

// Accessors
const sf::CircleShape &Ball::getShape() const { return this->shape; }

const int &Ball::getType() const { return this->type; }

// Public Functions
void Ball::update() {}

void Ball::render(sf::RenderTarget *target) { target->draw(this->shape); }
