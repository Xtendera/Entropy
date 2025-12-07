#include "player.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_surface.h"
#include <memory>

Player::Player(Engine *engine, double initialX, double initialY,
               std::vector<std::unique_ptr<Hitbox>> &tileHitboxes)
    : engine{engine}, playerSheet{nullptr}, keyA{false}, keyD{false},
      speed{700.0}, playerDirection{SDL_FLIP_NONE}, tileHitboxes{tileHitboxes} {
  playerX = initialX;
  playerY = initialY;

  animationTimer = std::make_unique<Timer>();

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

  playerSheet = std::make_unique<SpriteSheet>(playerTexture, 22, 22);

  playerHitbox = std::make_unique<Hitbox>(initialX, initialY,
                                          Player::HITBOX_WIDTH,
                                          Player::HITBOX_HEIGHT);

  playerMotion = std::make_unique<Motion>();
  playerMotion->position = initialY;

  this->initialX = initialX;
  this->initialY = initialY;
}

Player::~Player() {}

void Player::update(double deltaTime) {
  playerMotion->acceleration = isGrounded ? 0.0f : 1800.0f;

  playerMotion->update(deltaTime);
  playerY = playerMotion->position;

  isGrounded = false;

  playerHitbox->setPosition(playerX, playerY);

  for (const auto &hitbox : tileHitboxes) {
    CollisionResult result = playerHitbox->checkCollision(*hitbox);
    if (result.collided && result.hitTop && playerMotion->velocity >= 0.0f) {
      // Land on top of the tile
      playerMotion->velocity = 0.0f;
      playerMotion->acceleration = 0.0f;
      playerY = hitbox->getRect().y - playerHitbox->getRect().h;
      playerMotion->position = playerY;
      isGrounded = true;
    }
  }

  // if (playerMotion->position >= initialY && playerMotion->acceleration !=
  // 0.0f) {
  //   playerMotion->position = initialY;
  //   playerMotion->acceleration = 0.0f;
  //   playerMotion->velocity = 0;
  // }

  bool isWalking = false;

  if (keyD && !keyA) {
    if (playerDirection != SDL_FLIP_NONE) {
      playerDirection = SDL_FLIP_NONE;
    }
    playerX += speed * deltaTime;
    isWalking = true;
  } else if (keyA && !keyD) {
    if (playerDirection != SDL_FLIP_HORIZONTAL) {
      playerDirection = SDL_FLIP_HORIZONTAL;
    }
    playerX -= speed * deltaTime;
    isWalking = true;
  }

  int frameIndex = 0;

  if (isWalking && playerY == initialY) {
    if (!animationTimer->isStarted()) {
      animationTimer->start();
    }
    double frameDuration = 0.1;
    double elapsedSeconds = animationTimer->getTicksNS() / 1000000000.0;
    int walkFrame = (int)(elapsedSeconds / frameDuration) % 3;
    frameIndex = walkFrame + 1;
  } else {
    animationTimer->stop();
    if (playerY != initialY) {
      frameIndex = 4;
    }
  }

  const float renderHeight = 22.0f * Player::RENDER_SCALE;
  const float renderYOffset = renderHeight - Player::HITBOX_HEIGHT;

  playerSheet->renderFrame(playerX, playerY - renderYOffset, frameIndex,
                           Player::RENDER_SCALE, Player::RENDER_SCALE,
                           playerDirection);
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
      if (isGrounded && isDown) {
        playerMotion->velocity = -900.0f;
        playerMotion->acceleration = 1800.0f;
      }
      break;
    }
  }
}