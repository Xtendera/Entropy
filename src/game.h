#ifndef GAME_H
#define GAME_H
#pragma once

#include "engine/engine.h"

class Game {
public:
  Game(Engine *engine);
  ~Game();

  bool initialize();
  void update(float deltaTime);
  void handleInput(SDL_Event *event);

private:
  Engine *engine;
};

#endif
