#include "sandbox.h"

SandboxScene::SandboxScene(Engine *engine): engine{engine}, backgroundTexture{nullptr} {}

void SandboxScene::onEnter() {
  backgroundTexture = engine->getTextureManager()->getTexture("background");
}

void SandboxScene::onExit() {

}

void SandboxScene::update(Engine *engine, float deltaTime) {
  SDL_RenderClear(engine->getRenderer());

  if (backgroundTexture) {
    backgroundTexture->render(0, 0, 16.0f, 16.0f);
  }

  SDL_RenderPresent(engine->getRenderer());
}

void SandboxScene::handleInput(SDL_Event *event) {

}