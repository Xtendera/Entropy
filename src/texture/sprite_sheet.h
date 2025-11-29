#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H
#pragma once

#include "texture.h"

class SpriteSheet {
public:
  SpriteSheet(Texture *texture, int frameWidth, int frameHeight);
  void renderFrame(float x, float y, int frameIndex, float scaleX,
                   float scaleY);
  void renderFrame(float x, float y, int frameIndex);
  void renderTile(float x, float y, int col, int row);
  int getFrameWidth() { return frameWidth; };
  int getFrameHeight() { return frameHeight; };

private:
  Texture *baseTexture;
  int frameWidth, frameHeight;
  int columns, rows;
};
#endif