#include "sandbox.h"
#include <memory>
#include <cstdlib>
#include <ctime>

SandboxScene::SandboxScene(Engine *engine): engine{engine}, backgroundTexture{nullptr}, player{nullptr} {
  std::srand(std::time(nullptr));
  for (int i = 0; i < 270; i++) {
    SnowParticle particle;
    particle.x = std::rand() % 3840;
    particle.y = -100.0f - (std::rand() % 1000);
    particle.speed = 30.0f + (std::rand() % 30);
    particle.opacity = 100 + (std::rand() % 156);  // Range: 100-255
    snowParticles.push_back(particle);
  }

  if (!engine->getTextureManager()->getTexture("snow_tile")) {
    engine->getTextureManager()->loadTexture("snow_tile", engine->getBasePath() + "/assets/images/snow_tile_1.png");
  }
  snowTile = engine->getTextureManager()->getTexture("snow_tile");
}

void SandboxScene::onEnter() {
  backgroundTexture = engine->getTextureManager()->getTexture("background");
  player = std::make_unique<Player>(engine, 90.0f, 1808.0f - snowTile->getHeight() * 8.0f);
}

void SandboxScene::onExit() {
  player.reset();
}

void SandboxScene::drawSnow() {
  SDL_SetRenderDrawBlendMode(engine->getRenderer(), SDL_BLENDMODE_BLEND);
  for (const auto& particle : snowParticles) {
    SDL_SetRenderDrawColor(engine->getRenderer(), 255, 255, 255, particle.opacity);
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

  for (auto& particle : snowParticles) {
    particle.y += particle.speed * deltaTime;
    if (particle.y > 2160) {
      particle.y = -10.0f;
      particle.x = std::rand() % 3840;
      particle.speed = 50.0f + (std::rand() % 150);
    }
  }

  drawSnow();

  // Draw blocks
  for (int i = 0; i < 18; i++) {
    snowTile->render(i * snowTile->getWidth() * 8.0f, 2160 - (snowTile->getHeight() * 8.0f), 8.0f, 8.0f);
  }

  player->update(deltaTime);

  SDL_RenderPresent(engine->getRenderer());
}

void SandboxScene::handleInput(SDL_Event *event) {
  player->handleInput(event);
}