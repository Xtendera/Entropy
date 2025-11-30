#ifndef PLAYER_H
#define PLAYER_H
#include "SDL3/SDL_surface.h"
#include <memory>
#pragma once

#include "../engine/engine.h"
#include "../texture/sprite_sheet.h"
#include "../physics/motion.h"

class Player {
public:
  Player(Engine *engine, double initialX, double initialY);
  ~Player();
  void update(double deltaTime);
  void handleInput(SDL_Event *event);

private:
  double playerX, playerY, initialX, initialY;
  double speed;
  Engine *engine;
  // The kinematics engine is only used for vertical movement (1D).
  std::unique_ptr<Motion> playerMotion;
  std::unique_ptr<SpriteSheet> playerSheet;
  bool keyA, keyD;
  SDL_FlipMode playerDirection;
};

#endif