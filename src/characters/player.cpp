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

  bodyHitbox = std::make_unique<Hitbox>(initialX + 20, initialY + 10,
                                        Player::HITBOX_WIDTH - 40,
                                        Player::HITBOX_HEIGHT - 10);
  
  groundSensor = std::make_unique<Hitbox>(initialX + 30, initialY + Player::HITBOX_HEIGHT,
                                          Player::HITBOX_WIDTH - 60, 5);
  
  leftSensor = std::make_unique<Hitbox>(initialX - 5, initialY + 20,
                                        10, Player::HITBOX_HEIGHT - 40);
  
  rightSensor = std::make_unique<Hitbox>(initialX + Player::HITBOX_WIDTH - 5, initialY + 20,
                                         10, Player::HITBOX_HEIGHT - 40);
  
  ceilingSensor = std::make_unique<Hitbox>(initialX + 30, initialY - 5,
                                           Player::HITBOX_WIDTH - 60, 10);

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

  // Set every hitbox/sensor for the player.
  bodyHitbox->setPosition(playerX + 20, playerY + 10);
  groundSensor->setPosition(playerX + 30, playerY + Player::HITBOX_HEIGHT);
  leftSensor->setPosition(playerX - 5, playerY + 20);
  rightSensor->setPosition(playerX + Player::HITBOX_WIDTH - 5, playerY + 20);
  ceilingSensor->setPosition(playerX + 30, playerY - 5);

  isGrounded = false;
  for (const auto &hitbox : tileHitboxes) {
    if (groundSensor->intersects(*hitbox) && playerMotion->velocity >= 0.0f) {
      playerY = hitbox->getRect().y - Player::HITBOX_HEIGHT;
      playerMotion->position = playerY;
      playerMotion->velocity = 0.0f;
      playerMotion->acceleration = 0.0f;
      isGrounded = true;
      break;
    }
  }

  if (playerMotion->velocity < 0.0f) {
    ceilingSensor->setPosition(playerX + 30, playerY - 5);
    for (const auto &hitbox : tileHitboxes) {
      if (ceilingSensor->intersects(*hitbox)) {
        playerY = hitbox->getRect().y + hitbox->getRect().h + 5;
        playerMotion->position = playerY;
        playerMotion->velocity = 0.0f;
        break;
      }
    }
  }

  bodyHitbox->setPosition(playerX + 20, playerY + 10);
  groundSensor->setPosition(playerX + 30, playerY + Player::HITBOX_HEIGHT);
  leftSensor->setPosition(playerX - 5, playerY + 20);
  rightSensor->setPosition(playerX + Player::HITBOX_WIDTH - 5, playerY + 20);
  ceilingSensor->setPosition(playerX + 30, playerY - 5);

  bool isWalking = false;
  double moveX = 0.0;

  if (keyD && !keyA) {
    if (playerDirection != SDL_FLIP_NONE) {
      playerDirection = SDL_FLIP_NONE;
    }
    moveX = speed * deltaTime;
    isWalking = true;
  } else if (keyA && !keyD) {
    if (playerDirection != SDL_FLIP_HORIZONTAL) {
      playerDirection = SDL_FLIP_HORIZONTAL;
    }
    moveX = -speed * deltaTime;
    isWalking = true;
  }

  if (moveX != 0.0) {
    double newX = playerX + moveX;
    
    if (moveX > 0.0) {
      rightSensor->setPosition(newX + Player::HITBOX_WIDTH - 5, playerY + 20);
      bool blocked = false;
      for (const auto &hitbox : tileHitboxes) {
        if (rightSensor->intersects(*hitbox)) {
          blocked = true;
          break;
        }
      }
      if (!blocked) {
        playerX = newX;
      }
    } else {
      leftSensor->setPosition(newX - 5, playerY + 20);
      bool blocked = false;
      for (const auto &hitbox : tileHitboxes) {
        if (leftSensor->intersects(*hitbox)) {
          blocked = true;
          break;
        }
      }
      if (!blocked) {
        playerX = newX;
      }
    }
  }

  bodyHitbox->setPosition(playerX + 20, playerY + 10);
  groundSensor->setPosition(playerX + 30, playerY + Player::HITBOX_HEIGHT);
  leftSensor->setPosition(playerX - 5, playerY + 20);
  rightSensor->setPosition(playerX + Player::HITBOX_WIDTH - 5, playerY + 20);
  ceilingSensor->setPosition(playerX + 30, playerY - 5);

  int frameIndex = 0;

  if (isWalking && isGrounded) {
    if (!animationTimer->isStarted()) {
      animationTimer->start();
    }
    double frameDuration = 0.1;
    double elapsedSeconds = animationTimer->getTicksNS() / 1000000000.0;
    int walkFrame = (int)(elapsedSeconds / frameDuration) % 3;
    frameIndex = walkFrame + 1;
  } else {
    animationTimer->stop();
    if (!isGrounded) {
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
        playerMotion->velocity = -1050.0f;
        playerMotion->acceleration = 1800.0f;
      }
      break;
    }
  }
}

void Player::debugDrawHitboxes() {
  SDL_Renderer *renderer = engine->getRenderer();

  SDL_FRect bodyRect = bodyHitbox->getRect();
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderRect(renderer, &bodyRect);

  SDL_FRect groundRect = groundSensor->getRect();
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_RenderRect(renderer, &groundRect);

  SDL_FRect leftRect = leftSensor->getRect();
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderRect(renderer, &leftRect);

  SDL_FRect rightRect = rightSensor->getRect();
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderRect(renderer, &rightRect);

  SDL_FRect ceilingRect = ceilingSensor->getRect();
  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderRect(renderer, &ceilingRect);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for (const auto &hitbox : tileHitboxes) {
    SDL_FRect r = hitbox->getRect();
    SDL_RenderRect(renderer, &r);
  }
}