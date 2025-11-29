#ifndef BUTTON_H
#define BUTTON_H

#include "../engine/engine.h"
#include "../texture/sprite_sheet.h"
#include <memory>

// If button scaling is implemented, this will be required to be changed.
constexpr int BUTTON_WIDTH{37 * 16};
constexpr int BUTTON_HEIGHT{12 * 16};

class Button {
public:
  Button(Engine *engine, std::string btnText, float x, float y);
  void setFontSize(float fontSize);
  void render(float x, float y);
  int getWidth() { return BUTTON_WIDTH; };
  int getHeight() { return BUTTON_HEIGHT; };
  void handleInput(SDL_Event *event);
  bool isClicked();
private:
  Engine *engine;
  float fontSize;
  std::string btnText;
  std::unique_ptr<SpriteSheet> btnSheet;
  std::unique_ptr<Texture> btnTexture;
  float posX, posY;
  bool hovering;
  bool clicked;
};

#endif