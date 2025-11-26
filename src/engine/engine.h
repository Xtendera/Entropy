#ifndef ENGINE_H
#define ENGINE_H
#pragma once

#include "../emitter/emitter.h"
#include "../texture/texture_manager.h"
#include "../time/frame_manager.h"
#include "SDL3/SDL_render.h"
#include <memory>

class Engine {
public:
  Engine();
  ~Engine();

  bool initialize(int windowWidth, int windowHeight);
  void shutdown();

  SDL_Renderer *getRenderer() const { return renderer; }
  SDL_Window *getWindow() const { return window; }
  TextureManager *getTextureManager() { return textureManager.get(); }
  FrameManager *getFrameManager() { return frameManager.get(); }
  Emitter *getEmitter() { return emitter.get(); }
  int getWindowWidth() const { return windowX; }
  int getWindowHeight() const { return windowY; }

  int windowX;
  int windowY;

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  // This is the global textureManager. Subcomponents (e.g. levels) should
  // create their own.
  std::unique_ptr<TextureManager> textureManager;
  std::unique_ptr<Emitter> emitter;
  // Global font
  TTF_Font *gFont;
  std::unique_ptr<FrameManager> frameManager;
};
#endif