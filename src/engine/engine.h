#ifndef ENGINE_H
#define ENGINE_H
#pragma once

#include "../emitter/emitter.h"
#include "../texture/texture_manager.h"
#include "../time/frame_manager.h"
#include "SDL3/SDL_render.h"

class Engine {
public:
  Engine();
  ~Engine();

  bool initialize(int windowWidth, int windowHeight);
  void shutdown();

  SDL_Renderer *getRenderer() const { return renderer; }
  SDL_Window *getWindow() const { return window; }
  TextureManager *getTextureManager() { return textureManager; }
  FrameManager *getFrameManager() { return frameManager; }
  Emitter *getEmitter() { return emitter; }
  int getWindowWidth() const { return windowX; }
  int getWindowHeight() const { return windowY; }

  int windowX;
  int windowY;

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  // This is the global textureManager. Subcomponents (e.g. levels) should
  // create their own.
  TextureManager *textureManager;
  Emitter *emitter;
  // Global font
  TTF_Font *gFont;
  FrameManager *frameManager;
};
#endif