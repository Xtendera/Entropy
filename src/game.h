#ifndef GAME_H
#define GAME_H
#pragma once

#include "engine/engine.h"
#include "SDL3_ttf/SDL_ttf.h"

class Game {
public:
  Game(Engine* engine);
  ~Game();
  
  bool initialize();
  void render();
  void onWindowResize(SDL_Event *event);
  
private:
  Engine* engine;
  TTF_Font* font;
};

#endif
