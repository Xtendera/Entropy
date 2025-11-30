#include "player.h"

Player::Player(Engine *engine, double initialX, double initialY): engine{engine} {
  playerX = initialX;
  playerY = initialY;
  
  Texture *playerTexture = engine->getTextureManager()->getTexture("player");
  
  // Set playerTexture if it doesn't exist
  if (!playerTexture) {
    playerTexture = new Texture(engine->getRenderer());
    playerTexture->loadFromFile(engine->getBasePath() + "/assets/images/player.png");
    engine->getTextureManager()->addTexture("player", playerTexture);
  }

  playerSheet = new SpriteSheet(playerTexture, 21, 22);
}

void Player::update(double deltaTime) {
  
}