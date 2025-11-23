#ifndef EMITTER_H
#define EMITTER_H
#pragma once

#include "SDL3/SDL_events.h"
#include <map>
#include <vector>

class Emitter {
public:
  Emitter();
  void emitEvent(Uint32 type, SDL_Event *event);
  void registerCallback(Uint32 type, void (*callback)(SDL_Event *));

private:
  std::map<Uint32, std::vector<void (*)(SDL_Event *)>> eventMap;
};

#endif