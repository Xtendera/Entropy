#include "frame_manager.h"
#include "SDL3/SDL_timer.h"

FrameManager::FrameManager(): lastTime{0}, deltaTime{0}, frameCallbacks{} {}

FrameManager::~FrameManager() {}

void FrameManager::registerUpdate(void (*callback)(double)) {
    frameCallbacks.emplace_back(callback);
}

void FrameManager::update() {
    Uint64 newTimeNS = SDL_GetTicksNS();
    if (lastTime == 0) {
        lastTime = newTimeNS;
        deltaTime = 0.0;
        return;
    }

    deltaTime = static_cast<double>(newTimeNS - lastTime) / SDL_NS_PER_SECOND;
    lastTime = newTimeNS;

    for (auto callback : frameCallbacks) {
        callback(deltaTime);
    }
}