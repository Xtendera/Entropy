#include "game.h"
#include "levels/menu.h"

Game::Game(Engine *engine) : engine{engine} {}

Game::~Game() {}

bool Game::initialize() {
  sceneManager = std::make_unique<SceneManager>(engine);
  sceneManager->pushScene(std::make_unique<MenuScene>(engine));
  
  return true;
}

void Game::update(float deltaTime) {
  if (sceneManager) {
    sceneManager->update(deltaTime);
  }
}

void Game::handleInput(SDL_Event *event) {
  if (sceneManager) {
    sceneManager->handleInput(event);
  }
}
