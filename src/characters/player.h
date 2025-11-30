#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "../texture/sprite_sheet.h"
#include "../engine/engine.h"

class Player {
public:
  Player(Engine *engine, double initialX, double initialY);
  void update(double deltaTime);
private:
  double playerX, playerY;
  Engine *engine;
  SpriteSheet *playerSheet;
};

#endif