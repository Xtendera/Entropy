#ifndef TEXTURE_H
#define TEXTURE_H
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
  void render(float x, float y);
  void render(float x, float y, SDL_FRect *clip, float width, float height);
  int getWidth() { return width; };
  int getHeight() { return height; };

private:
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  int width;
  int height;
};
#endif