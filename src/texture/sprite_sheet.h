#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H
#pragma once

#include "texture.h"

class SpriteSheet {
public:
  SpriteSheet(Texture *texture, int frameWidth, int frameHeight);
  void renderFrame(float x, float y, int frameIndex, float scaleX = 1.0f,
                   float scaleY = 1.0f, SDL_FlipMode flipMode = SDL_FLIP_NONE);
  void renderTile(float x, float y, int col, int row,
                  SDL_FlipMode flipMode = SDL_FLIP_NONE);
  int getFrameWidth() { return frameWidth; };
  int getFrameHeight() { return frameHeight; };

private:
  Texture *baseTexture;
  int frameWidth, frameHeight;
  int columns, rows;
};
#endif