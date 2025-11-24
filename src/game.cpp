#include "game.h"
#include "SDL3/SDL_filesystem.h"
#include "SDL3/SDL_render.h"
#include <string>

Game::Game(Engine* engine) : engine{engine}, font{nullptr} {}

Game::~Game() {
  if (font) {
    TTF_CloseFont(font);
    font = nullptr;
  }
}

bool Game::initialize() {
  const char* basePath = SDL_GetBasePath();
  
  font = TTF_OpenFont((std::string(basePath) + "assets/font.ttf").c_str(), 48);
  if (!font) {
    SDL_Log("Failed to load font! SDL_ttf error: %s", SDL_GetError());
    SDL_free(const_cast<char*>(basePath));
    return false;
  }
  
  Texture* titleTexture = new Texture(engine->getRenderer());
  SDL_Color textColor = {255, 255, 255, 255};
  
  if (!titleTexture->loadFromRenderedText(font, "Entropy", textColor)) {
    delete titleTexture;
    SDL_free(const_cast<char*>(basePath));
    return false;
  }
  
  engine->getTextureManager()->addTexture("title", titleTexture);
  
  SDL_free(const_cast<char*>(basePath));
  return true;
}

void Game::render() {
  SDL_SetRenderDrawColorFloat(engine->getRenderer(), 0.0f, 0.0f, 0.0f,
                              SDL_ALPHA_OPAQUE_FLOAT);
  SDL_RenderClear(engine->getRenderer());
  
  Texture* titleTexture = engine->getTextureManager()->getTexture("title");
  if (titleTexture) {
    int windowWidth, windowHeight;
    SDL_GetRenderOutputSize(engine->getRenderer(), &windowWidth, &windowHeight);
    
    float x = (windowWidth - titleTexture->getWidth()) / 2.0f;
    float y = (windowHeight - titleTexture->getHeight()) / 2.0f;
    
    titleTexture->render(x, y);
  }
  
  SDL_RenderPresent(engine->getRenderer());
}
