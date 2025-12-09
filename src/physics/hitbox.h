#ifndef HITBOX_H
#define HITBOX_H
#include "SDL3/SDL_rect.h"
#pragma once

class Hitbox {
public:
  Hitbox(double x, double y, double width, double height);

  void setPosition(double x, double y);
  void setSize(double width, double height);

  SDL_FRect getRect() const { return rect; };

  bool intersects(const Hitbox &other) const;

private:
  SDL_FRect rect;
};

#endif