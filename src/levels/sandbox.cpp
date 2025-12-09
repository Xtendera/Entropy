#include "sandbox.h"
#include <cstdlib>
#include <ctime>
#include <memory>

SandboxScene::SandboxScene(Engine *engine)
    : engine{engine}, backgroundTexture{nullptr}, player{nullptr} {
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
  const int tileHeight = snowTile->getHeight() * 8;
  const float floorY = 8 * tileHeight;
  player = std::make_unique<Player>(
      engine, 90.0f, floorY - Player::HITBOX_HEIGHT,
      const_cast<std::vector<std::unique_ptr<Hitbox>> &>(grid->getHitboxes()));
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

  player->update(deltaTime);

  SDL_RenderPresent(engine->getRenderer());
}

void SandboxScene::handleInput(SDL_Event *event) { player->handleInput(event); }