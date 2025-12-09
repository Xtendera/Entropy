#include "sandbox.h"
#include <cstdlib>
#include <ctime>
#include <memory>

SandboxScene::SandboxScene(Engine *engine)
    : engine{engine}, backgroundTexture{nullptr}, pauseMenuTexture{nullptr}, player{nullptr} {
  std::srand(std::time(nullptr));
  for (int i = 0; i < 270; i++) {
    SnowParticle particle;
    particle.x = std::rand() % 3840;
    particle.y = -100.0f - (std::rand() % 1000);
    particle.speed = 30.0f + (std::rand() % 30);
    particle.opacity = 100 + (std::rand() % 156);
    snowParticles.push_back(particle);
  }

  if (!engine->getTextureManager()->getTexture("snow_tile")) {
    engine->getTextureManager()->loadTexture(
        "snow_tile", engine->getBasePath() + "/assets/images/snow_tile_1.png");
  }

  snowTile = engine->getTextureManager()->getTexture("snow_tile");

  const float scale = 8.0f;
  int tileWidth = snowTile->getWidth() * scale;
  int tileHeight = snowTile->getHeight() * scale;

  grid = std::make_unique<Grid>(15, 9, tileWidth, tileHeight);

  for (int col = 0; col < 15; col++) {
    auto hitbox = std::make_unique<Hitbox>(col * tileWidth, 8 * tileHeight,
                                           tileWidth, tileHeight);
    grid->setTile(col, 8, snowTile, std::move(hitbox));
  }

  auto hitbox = std::make_unique<Hitbox>(10 * tileWidth, 7 * tileHeight,
                                         tileWidth, tileHeight);
  grid->setTile(10, 7, snowTile, std::move(hitbox));
}

void SandboxScene::onEnter() {
  backgroundTexture = engine->getTextureManager()->getTexture("background");
  
  if (!engine->getTextureManager()->getTexture("pause_menu")) {
    engine->getTextureManager()->loadTexture(
        "pause_menu", engine->getBasePath() + "/assets/images/pause_menu.png");
  }
  pauseMenuTexture = engine->getTextureManager()->getTexture("pause_menu");
  
  const int tileHeight = snowTile->getHeight() * 8;
  const float floorY = 8 * tileHeight;
  player = std::make_unique<Player>(
      engine, 90.0f, floorY - Player::HITBOX_HEIGHT,
      const_cast<std::vector<std::unique_ptr<Hitbox>> &>(grid->getHitboxes()));
  
  float centerX = (3840.0f - BUTTON_WIDTH) / 2.0f;
  menuButton = std::make_unique<Button>(engine, "Menu", centerX, 1080.0f - 100.0f);
  quitButton = std::make_unique<Button>(engine, "Quit", centerX, 1080.0f + 100.0f);
}

void SandboxScene::onExit() { player.reset(); }

void SandboxScene::drawSnow() {
  SDL_SetRenderDrawBlendMode(engine->getRenderer(), SDL_BLENDMODE_BLEND);
  for (const auto &particle : snowParticles) {
    SDL_SetRenderDrawColor(engine->getRenderer(), 255, 255, 255,
                           particle.opacity);
    SDL_FRect rect = {particle.x, particle.y, 40.0f, 40.0f};
    SDL_RenderFillRect(engine->getRenderer(), &rect);
  }
  SDL_SetRenderDrawColor(engine->getRenderer(), 0, 0, 0, 255);
}

void SandboxScene::update(Engine *engine, float deltaTime) {
  SDL_RenderClear(engine->getRenderer());

  if (backgroundTexture) {
    backgroundTexture->render(0, 0, 16.0f, 16.0f);
  }

  for (auto &particle : snowParticles) {
    particle.y += particle.speed * deltaTime;
    if (particle.y > 2160) {
      particle.y = -10.0f;
      particle.x = std::rand() % 3840;
      particle.speed = 50.0f + (std::rand() % 150);
    }
  }

  drawSnow();

  grid->render(8.0f, 8.0f);

  if (!isPaused) {
    player->update(deltaTime);
  } else {
    player->update(0.0f);
  }

  if (isPaused && pauseMenuTexture) {
    const float scale = 16.0f;
    float menuWidth = pauseMenuTexture->getWidth() * scale;
    float menuHeight = pauseMenuTexture->getHeight() * scale;
    float centerX = (3840.0f - menuWidth) / 2.0f;
    float centerY = (2160.0f - menuHeight) / 2.0f;
    pauseMenuTexture->render(centerX, centerY, scale, scale);
    
    TTF_Font *font = engine->getGlobalFont();
    if (font) {
      SDL_Color white = {255, 255, 255, 255};
      SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Paused", 0, white);
      if (textSurface) {
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(engine->getRenderer(), textSurface);
        if (textTexture) {
          float textX = centerX + (menuWidth - textSurface->w) / 2.0f;
          float textY = centerY + 100.0f;
          SDL_FRect textRect = {textX, textY, (float)textSurface->w, (float)textSurface->h};
          SDL_RenderTexture(engine->getRenderer(), textTexture, nullptr, &textRect);
          SDL_DestroyTexture(textTexture);
        }
        SDL_DestroySurface(textSurface);
      }
    }
    
    if (menuButton && quitButton) {
      float centerX = (3840.0f - BUTTON_WIDTH) / 2.0f;
      menuButton->render(centerX, 980.0f);
      quitButton->render(centerX, 1230.0f);
    }
  }

  SDL_RenderPresent(engine->getRenderer());
}

void SandboxScene::handleInput(SDL_Event *event) {
  if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) {
    isPaused = !isPaused;
  }
  
  if (isPaused) {
    if (menuButton) menuButton->handleInput(event);
    if (quitButton) quitButton->handleInput(event);
    
    if (menuButton && menuButton->isClicked()) {
      engine->getSceneManager()->popScene();
      isPaused = false;
      return;
    }
    if (quitButton && quitButton->isClicked()) {
      SDL_Event quitEvent;
      quitEvent.type = SDL_EVENT_QUIT;
      SDL_PushEvent(&quitEvent);
    }
  } else {
    player->handleInput(event);
  }
}