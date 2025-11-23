#include "engine.h"
#include "SDL3/SDL_render.h"

Engine::Engine()
    : window(nullptr), renderer(nullptr), textureManager(nullptr),
      emitter(nullptr) {}

Engine::~Engine() {}

void Engine::shutdown() {
  if (textureManager) {
    delete textureManager;
    textureManager = nullptr;
  }
  if (emitter) {
    delete emitter;
    emitter = nullptr;
  }
  // Note: window and renderer are cleaned up by SDL automatically
}

bool Engine::initialize(int windowWidth, int windowHeight) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return false;
  }

  if (!SDL_CreateWindowAndRenderer("Entropy", windowWidth, windowHeight,
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return false;
  }

  SDL_SetRenderLogicalPresentation(renderer, windowWidth, windowHeight,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);

  if (TTF_Init() == false) {
    SDL_Log( "SDL_ttf could not initialize! SDL_ttf error: %s\n", SDL_GetError() );
    return false;
  }

  textureManager = new TextureManager(renderer);

  emitter = new Emitter();

  return true;
}