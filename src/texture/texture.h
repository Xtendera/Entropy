#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class Texture {
public:
  Texture(SDL_Renderer *renderer);
  ~Texture();
  bool loadFromFile(std::string path);
  void destroy();
  void render(float x, float y);
  int getWidth() { return width; };
  int getHeight() { return height; };

private:
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  int width;
  int height;
};
#endif