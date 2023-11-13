#pragma once

#include <SFML/Graphics.hpp>

class Ball {
 public:
  Ball();
  ~Ball();

  // Functions
  void update();
  void render(sf::RenderTarget* target);

 private:
  sf::CircleShape shape;

  void initShape();
};
