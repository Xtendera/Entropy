#ifndef TIMER_H
#define TIMER_H
#include "SDL3/SDL_stdinc.h"
#pragma once

// Based on
// https://lazyfoo.net/tutorials/SDL3/11-advanced-timers/index.php
class Timer {
public:
  Timer();
  ~Timer();

  // Actions
  void start();
  void stop();
  void pause();
  void unpause();

  // Get timer time
  Uint64 getTicksNS();

  // State getters
  bool isStarted() { return started; };
  bool isPaused() { return paused; };

private:
  Uint64 startTicks;
  Uint64 pausedTicks;

  bool paused;
  bool started;
};

#endif