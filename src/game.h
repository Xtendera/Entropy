#ifndef GAME_H
#define GAME_H
#pragma once

#include "SDL3_ttf/SDL_ttf.h"
#include "engine/engine.h"
#include "physics/motion.h"

class Game {
public:
  Game(Engine *engine);
  ~Game();

  bool initialize();
  void render();
  void onWindowResize(SDL_Event *event);

private:
  Engine *engine;
  TTF_Font *font;
  Motion *ball_motion;
  Motion *ball2_motion;
  Uint64 lastTime;
};

#endif
