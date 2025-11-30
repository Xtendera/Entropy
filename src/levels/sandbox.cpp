#include "sandbox.h"
#include <memory>

SandboxScene::SandboxScene(Engine *engine): engine{engine}, backgroundTexture{nullptr}, player{nullptr} {}

void SandboxScene::onEnter() {
  backgroundTexture = engine->getTextureManager()->getTexture("background");
  player = std::make_unique<Player>(engine, 60.0f, 1960.0f);
}

void SandboxScene::onExit() {
  player.reset();
}

void SandboxScene::update(Engine *engine, float deltaTime) {
  SDL_RenderClear(engine->getRenderer());

  if (backgroundTexture) {
    backgroundTexture->render(0, 0, 16.0f, 16.0f);
  }

  player->update(deltaTime);

  SDL_RenderPresent(engine->getRenderer());
}

void SandboxScene::handleInput(SDL_Event *event) {

}