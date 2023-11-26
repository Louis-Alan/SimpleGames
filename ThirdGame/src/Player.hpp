#pragma once

#include "SFML/Graphics/Texture.hpp"
#include <SFML/Graphics.hpp>

class Player {
 public:
    // Constructor / Destructor
    Player();
    ~Player();

    // Public functions
    void move(const float dirX, const float dirY);

    void update();
    void render(sf::RenderTarget *target);

 private:
    sf::Sprite sprite;
    sf::Texture texture;

    float movementSpeed;

    // Private functions
    void initTexture();
    void initSprite();
};
