#include "player.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_surface.h"
#include <memory>

Player::Player(Engine *engine, double initialX, double initialY)
    : engine{engine}, playerSheet{nullptr}, keyA{false}, keyD{false},
      speed{700.0}, playerDirection{SDL_FLIP_NONE} {
  playerX = initialX;
  playerY = initialY;

  Texture *playerTexture = engine->getTextureManager()->getTexture("player");

  if (!playerTexture) {
    if (!engine->getTextureManager()->loadTexture(
            "player", engine->getBasePath() + "assets/images/player.png")) {
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

  playerMotion = std::make_unique<Motion>();
  playerMotion->position = initialY;

  this->initialX = initialX;
  this->initialY = initialY;
}

Player::~Player() {}

void Player::update(double deltaTime) {

  playerMotion->update(deltaTime);

  if (playerMotion->position >= initialY && playerMotion->acceleration != 0.0f) {
    playerMotion->position = initialY;
    playerMotion->acceleration = 0.0f;
    playerMotion->velocity = 0;
  }

  playerY = playerMotion->position;

  if (keyD && !keyA) {
    if (playerDirection != SDL_FLIP_NONE) {
      playerDirection = SDL_FLIP_NONE;
    }
    playerX += speed * deltaTime;
  } else if (keyA && !keyD) {
    if (playerDirection != SDL_FLIP_HORIZONTAL) {
      playerDirection = SDL_FLIP_HORIZONTAL;
    }
    playerX -= speed * deltaTime;
  }

  playerSheet->renderFrame(playerX, playerY, 0, 16.0f, 16.0f, playerDirection);
}

void Player::handleInput(SDL_Event *event) {
  if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_KEY_UP) {
    bool isDown = (event->type == SDL_EVENT_KEY_DOWN);
    switch (event->key.key) {
    case SDLK_D:
      keyD = isDown;
      break;
    case SDLK_A:
      keyA = isDown;
      break;
    case SDLK_W:
      if (playerY == initialY && isDown) {
        playerMotion->velocity = -900.0f;
        playerMotion->acceleration = 1800.0f;
      }
    break;
    }
  }
}