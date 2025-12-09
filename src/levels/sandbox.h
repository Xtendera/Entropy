#ifndef SANDBOX_H
#define SANDBOX_H
#include <memory>
#pragma once

#include "../characters/player.h"
#include "../scene/scene.h"
#include "../grid/grid.h"
#include <vector>

struct SnowParticle {
  float x, y;
  float speed;
  int opacity;
};

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
  Texture *snowTile;
  std::unique_ptr<Player> player;
  std::vector<SnowParticle> snowParticles;
  std::unique_ptr<Grid> grid;
};

#endif