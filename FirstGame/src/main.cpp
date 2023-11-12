// "No Copyright 2023 Alan"

#include "celeste_lib.h"
#ifdef __APPLE__
#endif

#include "Game.hh"

int main() {
  // Init srand
  std::srand(static_cast<unsigned>(time(NULL)));

  // Init Game Engine
  Game game;

  // Game loop
  while (game.running() && !game.isGameOver()) {
    // Update
    game.update();

    // Render
    game.render();
  }

  return 0;
}
