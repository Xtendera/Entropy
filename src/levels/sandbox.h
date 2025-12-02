#ifndef SANDBOX_H
#define SANDBOX_H
#pragma once

#include "../scene/scene.h"
#include "../characters/player.h"
#include <vector>

class SandboxScene : public Scene {
public:
  SandboxScene(Engine *engine);

  void onEnter() override;
  void onExit() override;
  void update(Engine *engine, float deltaTime) override;
  void handleInput(SDL_Event *event) override;

private:
  void drawSnow();

  Engine *engine;
  Texture *backgroundTexture;
  std::unique_ptr<Player> player;
  
  struct SnowParticle {
    float x, y;
    float speed;
    int opacity;
  };
  std::vector<SnowParticle> snowParticles;
};

#endif