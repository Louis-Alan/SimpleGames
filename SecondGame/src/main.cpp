// Copyright [2023] Alan Louis

#include "Game.hpp"

int main() {
  // Initialize random seed
  srand(static_cast<unsigned>(time(0)));

  // Initialize Game object
  Game game;

  // Game loop
  while (game.running()) {
    game.update();
    game.render();
  }
}
