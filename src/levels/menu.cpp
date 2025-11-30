#include "menu.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "sandbox.h"
#include <memory>
#include <string>

MenuScene::MenuScene(Engine *engine)
    : engine{engine}, titleFont{nullptr}, titleTexture{nullptr},
      prevPlayBtn{false}, prevOptionsBtn{false}, prevQuitBtn{false} {}

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

  std::string fontPath =
      engine->getBasePath() + "/assets/fonts/science_gothic.ttf";

  titleFont = TTF_OpenFont(fontPath.c_str(), 256);

  if (!titleFont) {
    SDL_Log("Failed to load font! SDL_ttf error: %s", SDL_GetError());
    return;
  }

  titleTexture = new Texture(engine->getRenderer());
  SDL_Color white = {43, 43, 43, 255};

  if (!titleTexture->loadFromRenderedText(titleFont, "Entropy", white)) {
    SDL_Log("Failed to create title texture!");
    delete titleTexture;
    titleTexture = nullptr;
  }

  backgroundTexture = engine->getTextureManager()->getTexture("background");

  playBtnX = (engine->getWindowWidth() - BUTTON_WIDTH) * 0.5f;
  playBtnY = 700.0f;
  playBtn = std::make_unique<Button>(engine, "Play", playBtnX, playBtnY);
  if (!playBtn) {
    SDL_Log("Failed to create Play button");
  }

  optionsBtnX = (engine->getWindowWidth() - BUTTON_WIDTH) * 0.5f;
  optionsBtnY = 950.0f;
  optionsBtn =
      std::make_unique<Button>(engine, "Options", optionsBtnX, optionsBtnY);
  if (!optionsBtn) {
    SDL_Log("Failed to create Options button");
  }

  quitBtnX = (engine->getWindowWidth() - BUTTON_WIDTH) * 0.5f;
  quitBtnY = 1200.0f;
  quitBtn = std::make_unique<Button>(engine, "Quit", quitBtnX, quitBtnY);
  if (!quitBtn) {
    SDL_Log("Failed to create Quit button");
  }
}

void MenuScene::onExit() {}

void MenuScene::update(Engine *engine, float deltaTime) {
  SDL_RenderClear(engine->getRenderer());

  backgroundTexture->render(0, 0, 16.0f, 16.0f);

  if (titleTexture) {
    float x = (engine->getWindowWidth() - titleTexture->getWidth()) * 0.5f;
    float y = 200.0f;
    titleTexture->render(x, y);
  }

  playBtn->render(playBtnX, playBtnY);
  optionsBtn->render(optionsBtnX, optionsBtnY);
  quitBtn->render(quitBtnX, quitBtnY);

  if (!playBtn->isClicked() && prevPlayBtn) {
    engine->getSceneManager()->pushScene(
        std::make_unique<SandboxScene>(engine));
    return;
  }

  if (!optionsBtn->isClicked() && prevOptionsBtn) {
    // TODO: Handle Options event
  }

  if (!quitBtn->isClicked() && prevQuitBtn) {
    exit(0);
  }

  prevPlayBtn = playBtn->isClicked();
  prevOptionsBtn = optionsBtn->isClicked();
  prevQuitBtn = quitBtn->isClicked();

  SDL_RenderPresent(engine->getRenderer());
}

void MenuScene::handleInput(SDL_Event *event) {
  playBtn->handleInput(event);
  optionsBtn->handleInput(event);
  quitBtn->handleInput(event);
}
