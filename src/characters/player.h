#ifndef PLAYER_H
#define PLAYER_H
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
  double playerX, playerY;
  Engine *engine;
  std::unique_ptr<SpriteSheet> playerSheet;
  std::unique_ptr<Motion> playerMotion;
};

#endif