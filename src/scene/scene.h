#ifndef SCENE_H
#define SCENE_H
#pragma once

#include "../engine/engine.h"

class Scene {
public:
  virtual ~Scene() = default;

  virtual void onEnter() = 0;
  virtual void onExit() = 0;
  virtual void update(Engine *engine, float deltaTime) = 0;
  virtual void handleInput(SDL_Event *event) = 0;
};
#endif