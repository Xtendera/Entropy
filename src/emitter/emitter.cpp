#include "emitter.h"
#include "SDL3/SDL_stdinc.h"

Emitter::Emitter() {}

void Emitter::emitEvent(Uint32 type, SDL_Event *event) {
  auto it = eventMap.find(type);
  if (it == eventMap.end()) {
    return; // No callbacks for this EventType
  }
  const auto& callbacks = it->second;
  for (auto callback : callbacks) {
    callback(event);
  }
}

void Emitter::registerCallback(Uint32 type, void (*callback)(SDL_Event *)) {
  auto it = eventMap.find(type);
  if (it == eventMap.end()) {
    // EventType does not exist, add it and replace the iterator.
    eventMap.insert({type, { callback }});
  } else {
    it->second.push_back(callback);
  }
}