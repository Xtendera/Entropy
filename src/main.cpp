#include "SDL3/SDL_events.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

constexpr int kScreenWidth{640};
constexpr int kScreenHeight{480};

// The window we'll be rendering to
SDL_Window *gWindow{nullptr};

// The surface contained by the window
SDL_Surface *gScreenSurface{nullptr};

// The image we will load and show on the screen
SDL_Surface *gHelloWorld{nullptr};

bool init() {
  // Initialization flag
  bool success{true};

  // Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    if (gWindow = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3", kScreenWidth,
                                   kScreenHeight, 0);
        gWindow == nullptr) {
      SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Get window surface
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

void close() {
  // Clean up surface
  SDL_DestroySurface(gHelloWorld);
  gHelloWorld = nullptr;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;
  gScreenSurface = nullptr;

  // Quit SDL subsystems
  SDL_Quit();
}


int SDL_main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  int exitCode{0};
  if (!init()) {
    SDL_Log("Intialization Sequence failed! Exiting...");
    exitCode = 1;
  } else {
    bool quit{false};

    // The event data
    SDL_Event e;
    SDL_zero(e);

    while (!quit) {
      while (SDL_PollEvent(&e)) {
        // TODO: Add event manager here
        if (e.type == SDL_EVENT_QUIT) {
          quit = true;
        }
      }
      SDL_FillSurfaceRect(gScreenSurface, nullptr,
                          SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));
      SDL_UpdateWindowSurface(gWindow);
    }
  }
  close();

  return exitCode;
}
