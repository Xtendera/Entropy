#include "button.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_events.h"

Button::Button(Engine *engine, std::string btnText, float x, float y)
    : engine{engine}, btnSheet{nullptr}, hovering{false}, clicked{false}, posX{x}, posY{y} {
  if (!engine->getTextureManager()->getTexture("button")) {
    if (!engine->getTextureManager()->loadTexture(
            "button", engine->getBasePath() + "assets/images/button.png")) {
      return;
    }
  }
  Texture *tex = engine->getTextureManager()->getTexture("button");
  btnSheet = std::make_unique<SpriteSheet>(
      engine->getTextureManager()->getTexture("button"), 37, 12);

  if (TTF_GetFontSize(engine->getGlobalFont()) != 200.0f) {
    TTF_SetFontSize(engine->getGlobalFont(), 200.0f);
  }

  btnTexture = std::make_unique<Texture>(engine->getRenderer());

  if (!btnTexture->loadFromRenderedText(engine->getGlobalFont(), btnText,
                                        {255, 255, 255, 255})) {
    SDL_Log("Failed to create font texture: %s", SDL_GetError());
  }
}

void Button::setFontSize(float fontSize) {
  this->fontSize = fontSize;
}

void Button::handleInput(SDL_Event *event) {
  if (event->type == SDL_EVENT_MOUSE_MOTION) {
    float windowX = -1, windowY = -1;
    SDL_GetMouseState(&windowX, &windowY);

    float x, y;
    SDL_RenderCoordinatesFromWindow(engine->getRenderer(), windowX, windowY, &x,
                                    &y);

    if (x >= posX && x <= posX + getWidth() && y >= posY &&
        y <= posY + getHeight()) {
      hovering = true;
    } else {
      hovering = false;
    }
  }
  
  if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
    clicked = false;
  } else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    clicked = true;
  }
}

void Button::render(float x, float y) {
  float scaleX = 16.0f;
  float scaleY = 16.0f;

  if (posX != x) {
    posX = x;
  }

  if (posY != y) {
    posY = y;
  }

  btnSheet->renderFrame(x, y, 0, scaleX, scaleY);

  if (hovering) {
    btnSheet->renderFrame(x, y, 1, scaleX, scaleY);
  }

  float buttonWidth = btnSheet->getFrameWidth() * scaleX;
  float buttonHeight = btnSheet->getFrameHeight() * scaleY;

  float textX = x + (buttonWidth - btnTexture->getWidth()) * 0.5f;
  float textY = y + (buttonHeight - btnTexture->getHeight()) * 0.5f;

  btnTexture->render(textX, textY);
}

bool Button::isClicked() {
  return hovering && clicked;
}