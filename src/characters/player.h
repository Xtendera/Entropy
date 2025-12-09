#ifndef PLAYER_H
#define PLAYER_H
#include "SDL3/SDL_surface.h"
#include <memory>
#pragma once

#include "../engine/engine.h"
#include "../physics/hitbox.h"
#include "../physics/motion.h"
#include "../texture/sprite_sheet.h"
#include "../time/timer.h"
#include <vector>

class Player {
public:
  Player(Engine *engine, double initialX, double initialY,
         std::vector<std::unique_ptr<Hitbox>>& tileHitboxes);
  ~Player();
  void update(double deltaTime);
  void handleInput(SDL_Event *event);
  void debugDrawHitboxes();

  static constexpr float RENDER_SCALE = 16.0f;
  static constexpr float HITBOX_WIDTH = 22.0f * RENDER_SCALE;
  static constexpr float HITBOX_HEIGHT = 22.0f * RENDER_SCALE;

private:
  double playerX, playerY, initialX, initialY;
  double speed;
  bool isGrounded = false;
  Engine *engine;
  std::unique_ptr<Motion> playerMotion;
  std::unique_ptr<SpriteSheet> playerSheet;
  
  std::unique_ptr<Hitbox> bodyHitbox;
  std::unique_ptr<Hitbox> groundSensor;
  std::unique_ptr<Hitbox> leftSensor;
  std::unique_ptr<Hitbox> rightSensor;
  std::unique_ptr<Hitbox> ceilingSensor;
  
  std::unique_ptr<Timer> animationTimer;
  bool keyA, keyD;
  SDL_FlipMode playerDirection;
  std::vector<std::unique_ptr<Hitbox>>& tileHitboxes;
};

#endif