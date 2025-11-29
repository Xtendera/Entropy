#include "texture.h"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"

Texture::Texture(SDL_Renderer *renderer)
    : texture{nullptr}, width{0}, height{0}, renderer{renderer} {}

bool Texture::loadFromFile(std::string path) {
  destroy();
  SDL_Surface *surface = IMG_Load(path.c_str());
  if (!surface) {
    SDL_Log("Unable to load texture: %s", SDL_GetError());
    return false;
  }

  width = surface->w;
  height = surface->h;

  texture = SDL_CreateTextureFromSurface(renderer, surface);
  
  // Nearest-neighbhor scaling for pixelated textures
  if (texture) {
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
  }

  // Done with the surface, texture stores an internal copy
  SDL_DestroySurface(surface);
  return true;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool Texture::loadFromRenderedText(TTF_Font *font, std::string textureText,
                                   SDL_Color textColor) {
  destroy();

  SDL_Surface *textSurface =
      TTF_RenderText_Blended(font, textureText.c_str(), 0, textColor);
  if (textSurface == nullptr) {
    SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n",
            SDL_GetError());
    return false;
  }
  
  width = textSurface->w;
  height = textSurface->h;
  
  texture = SDL_CreateTextureFromSurface(renderer, textSurface);
  
  // Set nearest-neighbor filtering for pixel-perfect scaling
  if (texture) {
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
  }
  
  SDL_DestroySurface(textSurface);
  
  return texture != nullptr;
}
#endif

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

// You should probably not be calling this function without using a sprite sheet
// object
void Texture::render(float x, float y, SDL_FRect *clip, float width,
                     float height) {
  SDL_FRect dstRect{x, y, (float)width, (float)height};

  if (clip != nullptr) {
    dstRect.w = clip->w;
    dstRect.h = clip->h;
  }

  if (width > 0) {
    dstRect.w = width;
  }
  if (height > 0) {
    dstRect.h = height;
  }

  // srcrect = the clip rect
  SDL_RenderTexture(renderer, texture, clip, &dstRect);
}

Texture::~Texture() { destroy(); }
