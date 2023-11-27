#include "Bullet.hpp"
#include "SFML/Graphics/Rect.hpp"

Bullet::Bullet(const sf::Texture *texture, const float pos_x, const float pos_y,
               const float dir_x, const float dir_y, float speed) {

    this->shape.setTexture(*texture);
    this->shape.setPosition(pos_x, pos_y);
    this->direction.x = dir_x;
    this->direction.y = dir_y;
    this->movementSpeed = speed;
}

Bullet::~Bullet() {}

const sf::FloatRect Bullet::getBounds() const {
    return this->shape.getLocalBounds();
}

void Bullet::update() {
    this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget *target) { target->draw(this->shape); }
