#include "frame_manager.h"
#include "SDL3/SDL_timer.h"

FrameManager::FrameManager(): lastTime{0}, deltaTime{0} {}

FrameManager::~FrameManager() {}

void FrameManager::tick() {
    Uint64 newTimeNS = SDL_GetTicksNS();
    if (lastTime == 0) {
        lastTime = newTimeNS;
        deltaTime = 0.0;
        return;
    }

    deltaTime = static_cast<double>(newTimeNS - lastTime) / SDL_NS_PER_SECOND;
    lastTime = newTimeNS;
}