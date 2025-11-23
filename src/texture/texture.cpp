#include "texture.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"

Texture::Texture(SDL_Renderer *renderer)
    : texture{nullptr}, width{0}, height{0}, renderer{renderer} {}

bool Texture::loadFromFile(std::string path) {
  SDL_Surface *surface = IMG_Load(path.c_str());
  if (!surface) {
    SDL_Log("Unable to load texture: %s", SDL_GetError());
    return false;
  }

  width = surface->w;
  height = surface->h;

  texture = SDL_CreateTextureFromSurface(renderer, surface);

  // Done with the surface, texture stores an internal copy
  SDL_DestroySurface(surface);
  return true;
}

void Texture::destroy() {
  if (texture) {
    SDL_DestroyTexture(texture);
    texture = nullptr;
  }
  width = 0;
  height = 0;
}

void Texture::render(float x, float y) {
  SDL_FRect dstRect{x, y, (float)width, (float)height};

  SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
}

Texture::~Texture() { destroy(); }
