#ifndef GAME_H
#define GAME_H
#pragma once

#include "engine/engine.h"
#include "scene/scene_manager.h"
#include <memory>

class Game {
public:
  Game(Engine *engine);
  ~Game();

  bool initialize();
  void update(float deltaTime);
  void handleInput(SDL_Event *event);

private:
  Engine *engine;
  std::unique_ptr<SceneManager> sceneManager;
};

#endif
