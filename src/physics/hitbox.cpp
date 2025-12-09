#include "hitbox.h"
#include "SDL3/SDL_rect.h"

Hitbox::Hitbox(double x, double y, double width, double height) {
  rect = {static_cast<float>(x), static_cast<float>(y),
          static_cast<float>(width), static_cast<float>(height)};
}

void Hitbox::setPosition(double x, double y) {
  rect.x = x;
  rect.y = y;
}

void Hitbox::setSize(double width, double height) {
  rect.w = width;
  rect.h = height;
}

bool Hitbox::intersects(const Hitbox &other) const {
  return SDL_HasRectIntersectionFloat(&rect, &other.rect);
}