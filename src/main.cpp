#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL_events.h"
#include "engine/engine.h"
#include "game.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

constexpr int WINDOW_WIDTH{640};
constexpr int WINDOW_HEIGHT{480};

static Engine *engine = nullptr;
static Game *game = nullptr;

// Testing only
void mouseEvent(SDL_Event *event) { SDL_Log("Event triggered!"); }

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  SDL_SetAppMetadata("Entropy", "0.1", "dev.ashrayshah.entropy-engine");

  engine = new Engine();
  if (!engine->initialize(WINDOW_WIDTH, WINDOW_HEIGHT)) {
    return SDL_APP_FAILURE;
  }

  game = new Game(engine);
  if (!game->initialize()) {
    return SDL_APP_FAILURE;
  }

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
  game->render();
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  // Clean up game and engine before SDL destroys renderer
  if (game) {
    delete game;
    game = nullptr;
  }
  
  if (engine) {
    engine->shutdown();
    delete engine;
    engine = nullptr;
  }
}
