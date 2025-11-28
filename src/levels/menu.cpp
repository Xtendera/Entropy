#include "menu.h"
#include "SDL3/SDL_filesystem.h"
#include "SDL3/SDL_render.h"
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
  const char *basePath = SDL_GetBasePath();

  titleFont = TTF_OpenFont(
      (std::string(basePath) + "assets/fonts/science_gothic.ttf").c_str(), 144);
  
  if (!titleFont) {
    SDL_Log("Failed to load font! SDL_ttf error: %s", SDL_GetError());
    SDL_free(const_cast<char *>(basePath));
    return;
  }

  titleTexture = new Texture(engine->getRenderer());
  SDL_Color white = {255, 255, 255, 255};
  
  if (!titleTexture->loadFromRenderedText(titleFont, "Entropy", white)) {
    SDL_Log("Failed to create title texture!");
    delete titleTexture;
    titleTexture = nullptr;
  }
  
  SDL_free(const_cast<char *>(basePath));
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
  
  SDL_RenderPresent(engine->getRenderer());
}

void MenuScene::handleInput(SDL_Event *event) {
}
