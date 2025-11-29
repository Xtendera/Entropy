#ifndef MENU_H
#define MENU_H
#include <memory>
#pragma once

#include "../scene/scene.h"
#include "../texture/texture.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "../ui/button.h"

class MenuScene : public Scene {
public:
  MenuScene(Engine *engine);
  ~MenuScene();

  void onEnter() override;
  void onExit() override;
  void update(Engine *engine, float deltaTime) override;
  void handleInput(SDL_Event *event) override;

private:
  Engine *engine;
  TTF_Font *titleFont;
  Texture *titleTexture;
  std::unique_ptr<Button> playBtn;
  float playBtnX, playBtnY;
};

#endif
