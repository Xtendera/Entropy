#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include <vector>
#pragma once

class Engine;
class Scene;
#include <memory>
#include "SDL3/SDL_events.h"

class SceneManager {
public:
  SceneManager(Engine *engine);
  void pushScene(std::unique_ptr<Scene> scene);
  void popScene();
  void changeScene(std::unique_ptr<Scene> scene);

  void update(float deltaTime);  // Handles both logic and rendering
  void handleInput(SDL_Event *event);
  
  Scene* getCurrentScene();
  bool isEmpty() const { return sceneStack.empty(); }

private:
  std::vector<std::unique_ptr<Scene>> sceneStack;
  Engine *engine;
};

#endif