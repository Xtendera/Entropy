#ifndef TEXTURE_H
#define TEXTURE_H
#include "SDL3/SDL_surface.h"
#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "SDL3_ttf/SDL_ttf.h"

class Texture {
public:
  Texture(SDL_Renderer *renderer);
  ~Texture();
  bool loadFromFile(std::string path);
#if defined(SDL_TTF_MAJOR_VERSION)
  // Creates texture from text
  bool loadFromRenderedText(TTF_Font *font, std::string textureText, SDL_Color textColor);
#endif
  void destroy();
  void render(float x, float y, float scaleX = 1.0f, float scaleY = 1.0f, SDL_FlipMode flipMode = SDL_FLIP_NONE);
  void render(float x, float y, SDL_FRect *clip, float width, float height, SDL_FlipMode flipMode = SDL_FLIP_NONE);
  int getWidth() { return width; };
  int getHeight() { return height; };

private:
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  int width;
  int height;
};
#endif