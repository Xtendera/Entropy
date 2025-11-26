#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <memory>
#pragma once

#include "SDL3/SDL_render.h"
#include "texture.h"
#include <map>

class TextureManager {
public:
  TextureManager(SDL_Renderer *renderer);
  ~TextureManager();
  bool loadTexture(std::string key, std::string filePath);
  void addTexture(std::string key, Texture* texture);
  Texture* getTexture(std::string key);
  bool destroyTexture(std::string key);
private:
  SDL_Renderer *renderer;
  std::map<std::string, std::unique_ptr<Texture>> texMap;
};
#endif