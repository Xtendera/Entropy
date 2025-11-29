#ifndef BUTTON_H
#define BUTTON_H

#include "../engine/engine.h"
#include "../texture/sprite_sheet.h"
#include <memory>

// If button scaling is implemented, this will be required to be changed.
constexpr int width{37 * 16};
constexpr int height{12 * 16};

class Button {
public:
  Button(Engine *engine, std::string btnText, float x, float y);
  void render(float x, float y);
  int getWidth() { return width; };
  int getHeight() { return height; };
  void handleInput(SDL_Event *event);
private:
  Engine *engine;
  std::string btnText;
  std::unique_ptr<SpriteSheet> btnSheet;
  std::unique_ptr<Texture> btnTexture;
  float posX, posY;
  bool hovering;
};

#endif