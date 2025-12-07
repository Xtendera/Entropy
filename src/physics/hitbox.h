#ifndef HITBOX_H
#define HITBOX_H
#include "SDL3/SDL_rect.h"
#pragma once

struct CollisionResult {
  bool collided;
  bool hitTop, hitBottom, hitLeft, hitRight;
};

class Hitbox {
public:
  Hitbox(double x, double y, double width, double height);

  void setPosition(double x, double y);
  void setSize(double width, double height);

  SDL_FRect getRect() { return rect; };

  CollisionResult checkCollision(const Hitbox &b);

private:
  SDL_FRect rect;
};

#endif