#ifndef FRAME_MANAGER_H
#define FRAME_MANAGER_H
#pragma once

#include "SDL3/SDL_stdinc.h"

class FrameManager {
public:
  FrameManager();
  ~FrameManager();

  void tick();  // Call once per frame to update deltaTime
  double getDeltaTime() { return deltaTime; };

private:
  Uint64 lastTime;
  double deltaTime;
};

#endif