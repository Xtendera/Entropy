#ifndef EMITTER_H
#define EMITTER_H
#pragma once

#include "SDL3/SDL_events.h"
#include <map>
#include <vector>

class Emitter {
public:
  Emitter();
  void emitEvent(SDL_EventType type, SDL_Event *event);
  void registerCallback(SDL_EventType type, void (*callback)(SDL_Event *));

private:
  std::map<SDL_EventType, std::vector<void (*)(SDL_Event *)>> eventMap;
};

#endif