#include "texture.h"

Texture::Texture(std::string path) {
  SDL_Surface *surface = SDL_LoadPNG(path);
}
