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
CollisionResult Hitbox::checkCollision(const Hitbox &b) {
  CollisionResult result{false, false, false, false, false};

  SDL_FRect intersection;

  if (!SDL_GetRectIntersectionFloat(&rect, &b.rect, &intersection)) {
    return result; // No collision
  }

  result.collided = true;

  float overlapX = intersection.w;
  float overlapY = intersection.h;

  const float THRESHOLD = 0.1f;

  if (overlapY <= THRESHOLD || overlapY <= overlapX) {
    if (rect.y < b.rect.y) {
      result.hitTop = true;
    } else {
      result.hitBottom = true;
    }
  }

  if (overlapX <= THRESHOLD || overlapX <= overlapY) {
    if (rect.x < b.rect.x) {
      result.hitRight = true;
    } else {
      result.hitLeft = true;
    }
  }

  return result;
}