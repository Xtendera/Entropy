#include "menu.h"
#include "SDL3/SDL_render.h"
#include <memory>
#include <string>

MenuScene::MenuScene(Engine *engine) 
    : engine{engine}, titleFont{nullptr}, titleTexture{nullptr} {}

MenuScene::~MenuScene() {
  if (titleTexture) {
    delete titleTexture;
    titleTexture = nullptr;
  }
  if (titleFont) {
    TTF_CloseFont(titleFont);
    titleFont = nullptr;
  }
}

void MenuScene::onEnter() {
  std::string fontPath = engine->getBasePath() + "/assets/fonts/science_gothic.ttf";

  titleFont = TTF_OpenFont(fontPath.c_str(), 196);
  
  if (!titleFont) {
    SDL_Log("Failed to load font! SDL_ttf error: %s", SDL_GetError());
    return;
  }

  titleTexture = new Texture(engine->getRenderer());
  SDL_Color white = {255, 255, 255, 255};
  
  if (!titleTexture->loadFromRenderedText(titleFont, "Entropy", white)) {
    SDL_Log("Failed to create title texture!");
    delete titleTexture;
    titleTexture = nullptr;
  }

  playBtnX = (engine->getWindowWidth() - width) * 0.5f;
  playBtnY = 600.0f;
  playBtn = std::make_unique<Button>(engine, "Play", playBtnX, playBtnY);
}

void MenuScene::onExit() {
}

void MenuScene::update(Engine *engine, float deltaTime) {
  SDL_SetRenderDrawColor(engine->getRenderer(), 25, 25, 50, 255);
  SDL_RenderClear(engine->getRenderer());
  
  if (titleTexture) {
    float x = (engine->getWindowWidth() - titleTexture->getWidth()) * 0.5f;
    float y = 200.0f;
    titleTexture->render(x, y);
  }

  if (playBtn) {
    playBtn->render(playBtnX, playBtnY);
  }
  
  SDL_RenderPresent(engine->getRenderer());
}

void MenuScene::handleInput(SDL_Event *event) {
  if (playBtn) {
    playBtn->handleInput(event);
  }
}
