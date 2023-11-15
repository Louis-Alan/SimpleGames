#pragma once

#include <SFML/Graphics.hpp>

enum BallType { DEFAULT = 0, DAMAGING, HEALING, NROFTYPES };

class Ball {
 public:
    Ball(const sf::RenderWindow &window, int type);
    ~Ball();

    // Accessors
    const sf::CircleShape &getShape() const;
    const int &getType() const;

    // Functions
    void update();
    void render(sf::RenderTarget *target);

 private:
    sf::CircleShape shape;

    int type;

    void initShape(const sf::RenderWindow &window);
};
