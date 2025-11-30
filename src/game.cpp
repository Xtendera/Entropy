#include "game.h"
#include "levels/menu.h"

Game::Game(Engine *engine) : engine{engine} {}

Game::~Game() {}

bool Game::initialize() {
  // Initialize the background that will be used in the menu and elseware
  engine->getTextureManager()->loadTexture("background", engine->getBasePath() + "/assets/images/background.png");
  engine->getSceneManager()->pushScene(std::make_unique<MenuScene>(engine));
  return true;
}

void Game::update(float deltaTime) {
  engine->getSceneManager()->update(deltaTime);
}

void Game::handleInput(SDL_Event *event) {
  engine->getSceneManager()->handleInput(event);
}
