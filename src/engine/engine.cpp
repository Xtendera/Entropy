#include "engine.h"
#include "SDL3/SDL_render.h"
#include <memory>

Engine::Engine()
    : window{nullptr}, renderer{nullptr}, windowX{0}, windowY{0}, gFont{nullptr} {}

Engine::~Engine() {}

void Engine::shutdown() {
  if (gFont) {
    TTF_CloseFont(gFont);
    gFont = nullptr;
  }
  
  textureManager.reset();
  emitter.reset();
  frameManager.reset();
  
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }
  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
  TTF_Quit();
  SDL_Quit();
}

bool Engine::initialize(int windowWidth, int windowHeight) {
  windowX = windowWidth;
  windowY = windowHeight;
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return false;
  }

  if (!SDL_CreateWindowAndRenderer("Entropy", windowWidth, windowHeight,
                                   SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED, &window, &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return false;
  }

  if (!SDL_SetRenderLogicalPresentation(renderer, windowWidth, windowHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX)) {
    SDL_Log("Couldn't set logical presentation: %s", SDL_GetError());
    return false;
  }

  if (TTF_Init() == false) {
    SDL_Log( "SDL_ttf could not initialize! SDL_ttf error: %s\n", SDL_GetError() );
    return false;
  }

  frameManager = std::make_unique<FrameManager>();

  textureManager = std::make_unique<TextureManager>(renderer);

  emitter = std::make_unique<Emitter>();

  const char *basePathC = SDL_GetBasePath();

  // Store the basePath as an object in the Engine for future use.
  basePath = std::string(basePathC);

  SDL_free(const_cast<char *>(basePathC));

  gFont = TTF_OpenFont(
      (basePath + "assets/fonts/byte_bounce.ttf").c_str(), 144);
  
  if (!gFont) {
    SDL_Log("Failed to load font! SDL_ttf error: %s", SDL_GetError());
    return false;
  }

  return true;
}