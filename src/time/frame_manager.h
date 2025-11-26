#ifndef FRAME_MANAGER_H
#define FRAME_MANAGER_H
#pragma once

#include "SDL3/SDL_stdinc.h"
#include <vector>

class FrameManager {
public:
  FrameManager();
  ~FrameManager();

  void registerUpdate(void (*callback)(double));

  void update();
  double getDeltaTime() { return deltaTime; };

private:
  Uint64 lastTime;
  double deltaTime;
  std::vector<void (*)(double)> frameCallbacks;
};

#endif