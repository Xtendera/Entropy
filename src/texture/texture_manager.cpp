#include "texture_manager.h"

TextureManager::TextureManager(SDL_Renderer *renderer) {
  this->renderer = renderer;
}

TextureManager::~TextureManager() {
  texMap.clear();
}

bool TextureManager::loadTexture(std::string key, std::string filePath) {
  std::unique_ptr<Texture> tex = std::make_unique<Texture>(renderer);
  if (!tex->loadFromFile(filePath)) {
    tex->destroy();
    return false;
  }
  
  auto it = texMap.find(key);
  if (it != texMap.end()) {
    it->second->destroy();
  }
  
  texMap[key] = std::move(tex);
  return true;
}

void TextureManager::addTexture(std::string key, Texture* texture) {
  auto it = texMap.find(key);
  if (it != texMap.end()) {
    it->second->destroy();
  }
  texMap[key] = std::unique_ptr<Texture>(texture);
}

Texture* TextureManager::getTexture(std::string key) {
  auto it = texMap.find(key);
  if (it != texMap.end()) {
    return it->second.get();
  }
  return nullptr;
}

bool TextureManager::destroyTexture(std::string key) {
  auto it = texMap.find(key);
  if (it == texMap.end()) {
    return false;
  }
  it->second->destroy();
  texMap.erase(it);
  return true;
}