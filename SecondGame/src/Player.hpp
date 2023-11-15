// Copyright [2023] Alan Louis
#pragma once

#include <SFML/Graphics.hpp>

class Player {
 public:
    Player(float x = 0.f, float y = 0.f);
    ~Player();

    void update(const sf::RenderTarget *target);
    void render(sf::RenderTarget *target);

    // Accessors
    const sf::RectangleShape &getShape() const;
    const int &getHp() const;
    const int &getHpMax() const;

    // Game logic functions
    void takeDamage(int damage);
    void gainHealth(int health);

 private:
    sf::RectangleShape shape;

    float movementSpeed;
    int hp;
    int hpMax;

    void updateInput();
    void updateWindowBoundsCollision(const sf::RenderTarget *target);

    void initVariables();
    void initShape();
};
