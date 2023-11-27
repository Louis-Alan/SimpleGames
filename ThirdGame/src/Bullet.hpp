#pragma once

#include "SFML/Graphics/Rect.hpp"
#include <SFML/Graphics.hpp>

class Bullet {
 public:
    Bullet(const sf::Texture *texture, const float pos_x, const float pos_y,
           const float dir_x, const float dir_y, float speed);
    ~Bullet();

    // Acesors
    const sf::FloatRect getBounds() const;

    void update();
    void render(sf::RenderTarget *target);

 private:
    sf::Sprite shape;

    sf::Vector2f direction;
    float movementSpeed;

    // Init texture
    void initTexture();
    void initShape();
};
