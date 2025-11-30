#include "scene_manager.h"
#include "scene.h"

SceneManager::SceneManager(Engine *engine) : engine{engine}, sceneStack{} {}

SceneManager::~SceneManager() {}

void SceneManager::pushScene(std::unique_ptr<Scene> scene) {
  if (!sceneStack.empty()) {
    sceneStack.back()->onExit();
  }
  sceneStack.push_back(std::move(scene));
  sceneStack.back()->onEnter();
}

void SceneManager::popScene() {
  if (sceneStack.empty()) {
    return;
  }

  sceneStack.back()->onExit();
  sceneStack.pop_back();

  if (!sceneStack.empty()) {
    sceneStack.back()->onEnter();
  }
}

void SceneManager::changeScene(std::unique_ptr<Scene> scene) {
  if (!sceneStack.empty()) {
    sceneStack.back()->onExit();
    sceneStack.pop_back();
  }
  sceneStack.push_back(std::move(scene));
  sceneStack.back()->onEnter();
}

void SceneManager::update(float deltaTime) {
  if (!sceneStack.empty()) {
    // Updates logic AND renders
    // TODO: Have a fixedUpdate() and update()/render() methods seperately
    // (would require serious lerping)
    sceneStack.back()->update(engine, deltaTime);
  }
}

void SceneManager::handleInput(SDL_Event *event) {
  if (!sceneStack.empty()) {
    sceneStack.back()->handleInput(event);
  }
}

Scene *SceneManager::getCurrentScene() {
  if (sceneStack.empty()) {
    return nullptr;
  }
  return sceneStack.back().get();
}