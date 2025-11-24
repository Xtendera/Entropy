#include "texture_manager.h"

TextureManager::TextureManager(SDL_Renderer *renderer) {
  this->renderer = renderer;
}

TextureManager::~TextureManager() {
  for (auto& pair : texMap) {
    delete pair.second;
  }
  texMap.clear();
}

bool TextureManager::loadTexture(std::string key, std::string filePath) {
  Texture *tex = new Texture(renderer);
  if (!tex->loadFromFile(filePath)) {
    delete tex;
    return false;
  }
  
  auto it = texMap.find(key);
  if (it != texMap.end()) {
    delete it->second;
  }
  
  texMap[key] = tex;
  return true;
}

void TextureManager::addTexture(std::string key, Texture* texture) {
  auto it = texMap.find(key);
  if (it != texMap.end()) {
    delete it->second;
  }
  texMap[key] = texture;
}

Texture* TextureManager::getTexture(std::string key) {
  auto it = texMap.find(key);
  if (it != texMap.end()) {
    return it->second;
  }
  return nullptr;
}

bool TextureManager::destroyTexture(std::string key) {
  auto it = texMap.find(key);
  if (it == texMap.end()) {
    return false;
  }
  delete it->second;
  texMap.erase(it);
  return true;
}