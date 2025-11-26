#include "game.h"
#include "SDL3/SDL_filesystem.h"
#include "SDL3/SDL_render.h"
#include "physics/motion.h"
#include <string>

static Game *g_gameInstance = nullptr;

Game::Game(Engine *engine) : engine{engine}, font{nullptr} {
  g_gameInstance = this;
}

Game::~Game() {
  g_gameInstance = nullptr;
  if (ball_motion) {
    delete ball_motion;
    ball_motion = nullptr;
  }
  if (ball2_motion) {
    delete ball2_motion;
    ball2_motion = nullptr;
  }
  if (font) {
    TTF_CloseFont(font);
    font = nullptr;
  }
}

bool Game::initialize() {
  const char *basePath = SDL_GetBasePath();

  int fontSize = engine->getWindowHeight() / 15;
  font = TTF_OpenFont((std::string(basePath) + "assets/font.ttf").c_str(), fontSize);
  if (!font) {
    SDL_Log("Failed to load font! SDL_ttf error: %s", SDL_GetError());
    SDL_free(const_cast<char *>(basePath));
    return false;
  }

  Texture *titleTexture = new Texture(engine->getRenderer());
  SDL_Color textColor = {255, 255, 255, 255};

  if (!titleTexture->loadFromRenderedText(font, "Entropy Engine", textColor)) {
    delete titleTexture;
    SDL_free(const_cast<char *>(basePath));
    return false;
  }

  engine->getTextureManager()->addTexture("title", titleTexture);
  engine->getTextureManager()->loadTexture("ball", std::string(basePath) +
                                                       "assets/demo_ball.png");

  ball_motion = new Motion();

  ball_motion->position = 0.0;
  ball_motion->velocity = 0.0;
  ball_motion->acceleration = 500.0;

  ball2_motion = new Motion();

  // Use logical size for positioning
  ball2_motion->position = engine->getWindowHeight() * 0.75;
  ball2_motion->velocity = 0.0;
  ball2_motion->acceleration = 500.0;

  lastTime = SDL_GetTicksNS();

  SDL_free(const_cast<char *>(basePath));
  return true;
}

void Game::render() {
  Uint64 currentTime = SDL_GetTicksNS();
  double deltaTime = (currentTime - lastTime) / 1000000000.0;
  lastTime = currentTime;

  ball_motion->update(deltaTime);
  ball2_motion->update(deltaTime);

  SDL_SetRenderDrawColorFloat(engine->getRenderer(), 0.0f, 0.0f, 0.0f,
                              SDL_ALPHA_OPAQUE_FLOAT);
  SDL_RenderClear(engine->getRenderer());

  Texture *titleTexture = engine->getTextureManager()->getTexture("title");
  if (titleTexture) {
    float x = (engine->getWindowWidth() - titleTexture->getWidth()) * 0.5f;
    float y = (engine->getWindowHeight() - titleTexture->getHeight()) * 0.5f;

    titleTexture->render(x, y);
  }

  Texture *ballTexture = engine->getTextureManager()->getTexture("ball");
  if (ballTexture) {
    float ballX = engine->getWindowWidth() * 0.25f - ballTexture->getWidth() * 0.5f;
    float ballY = (float)ball_motion->position;

    if (ballY >= engine->getWindowHeight() * 0.75) {
      // Ball is at the "bounce" level, so reverse the velocity
      ball_motion->velocity = -800.0f;
    }

    ballTexture->render(ballX, ballY);
  }

  if (ballTexture) {
    float ball2X = engine->getWindowWidth() * 0.75f - ballTexture->getWidth() * 0.5f;
    float ball2Y = (float)ball2_motion->position;

    if (ball2Y >= engine->getWindowHeight() * 0.75) {
      ball2_motion->velocity = -800.0f;
    }

    ballTexture->render(ball2X, ball2Y);
  }

  SDL_RenderPresent(engine->getRenderer());
}
