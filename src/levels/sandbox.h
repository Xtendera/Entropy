#ifndef SANDBOX_H
#define SANDBOX_H
#pragma once

#include "../scene/scene.h"

class SandboxScene : public Scene {
public:
  SandboxScene(Engine *engine);

  void onEnter() override;
  void onExit() override;
  void update(Engine *engine, float deltaTime) override;
  void handleInput(SDL_Event *event) override;

private:
  Engine *engine;
  Texture *backgroundTexture;
};

#endif