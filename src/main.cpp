#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL_events.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "engine/engine.h"

constexpr int WINDOW_WIDTH{640};
constexpr int WINDOW_HEIGHT{480};

static Engine *engine = nullptr;

// Testing only
void mouseEvent(SDL_Event *event) {
  SDL_Log("Event triggered!");
}

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  SDL_SetAppMetadata("Entropy", "0.1", "dev.ashrayshah.entropy-engine");

  engine = new Engine();
  if (!engine->initialize(WINDOW_WIDTH, WINDOW_HEIGHT)) {
    return SDL_APP_FAILURE;
  }

  const char *basePath = SDL_GetBasePath();

  // Initialize textures
  if (!engine->getTextureManager()->loadTexture("test", std::string(basePath) + "assets/test.png")) {
    return SDL_APP_FAILURE;
  }

  SDL_free(const_cast<char *>(basePath));

  engine->getEmitter()->registerCallback(SDL_EVENT_MOUSE_WHEEL, mouseEvent);

  return SDL_APP_CONTINUE;
}

// AppEvent handler
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS; /* end the program, reporting success to the OS. */
  }
  
  // Event Emitter
  engine->getEmitter()->emitEvent(event->type, event);

  return SDL_APP_CONTINUE; /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate) {
  const double now = ((double)SDL_GetTicks()) / 1000.0;
  const float red = (float)(0.5 + 0.5 * SDL_sin(now));
  const float green = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
  const float blue = (float)(0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
  SDL_SetRenderDrawColorFloat(engine->getRenderer(), red, green, blue,
                              SDL_ALPHA_OPAQUE_FLOAT);

  /* clear the window to the draw color. */
  SDL_RenderClear(engine->getRenderer());

  // Render texture
  engine->getTextureManager()->getTexture("test")->render(0.0f, 0.0f);

  /* put the newly-cleared rendering on the screen. */
  SDL_RenderPresent(engine->getRenderer());

  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  // Clean up engine before SDL destroys renderer
  if (engine) {
    engine->shutdown();
    delete engine;
    engine = nullptr;
  }
}
