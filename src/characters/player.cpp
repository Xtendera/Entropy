#include "player.h"

Player::Player(Engine *engine, double initialX, double initialY): engine{engine}, playerMotion{nullptr}, playerSheet{nullptr} {
  playerX = initialX;
  playerY = initialY;
  
  Texture *playerTexture = engine->getTextureManager()->getTexture("player");
  
  if (!playerTexture) {
    if (!engine->getTextureManager()->loadTexture("player", 
        engine->getBasePath() + "assets/images/player.png")) {
      SDL_Log("Player: Failed to load player texture!");
      return;
    }
    playerTexture = engine->getTextureManager()->getTexture("player");
  }

  if (!playerTexture) {
    SDL_Log("Player texture is null after loading!");
    return;
  }

  playerSheet = std::make_unique<SpriteSheet>(playerTexture, 21, 22);
}

Player::~Player() {}

void Player::update(double deltaTime) {
  playerSheet->renderFrame(playerX, playerY, 0, 16.0f, 16.0f);
}