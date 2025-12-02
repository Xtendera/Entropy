#include "timer.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_timer.h"

Timer::Timer() : startTicks{0}, pausedTicks{0}, paused{false}, started{false} {}

Timer::~Timer() {}

void Timer::start() {
  started = true;
  paused = false;

  startTicks = SDL_GetTicksNS();
  pausedTicks = 0;
}

void Timer::stop() {
  started = false;
  paused = false;

  startTicks = 0;
  pausedTicks = 0;
}

void Timer::pause() {
  if (started && !paused) {
    paused = true;

    pausedTicks = SDL_GetTicksNS() - startTicks;
    started = 0;
  }
}

void Timer::unpause() {
  if (started && paused) {
    paused = false;

    startTicks = SDL_GetTicksNS() - pausedTicks;

    pausedTicks = 0;
  }
}

Uint64 Timer::getTicksNS() {
  if (started) {
    if (paused) {
      return pausedTicks;
    }
    return SDL_GetTicksNS() - startTicks;
  }
  return 0;
}