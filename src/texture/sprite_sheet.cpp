#include "sprite_sheet.h"

SpriteSheet::SpriteSheet(Texture *texture, int frameWidth, int frameHeight)
    : baseTexture{texture}, frameWidth{frameWidth}, frameHeight{frameHeight} {
  columns = texture->getWidth() / frameWidth;
  rows = texture->getHeight() / frameHeight;
}

void SpriteSheet::renderFrame(float x, float y, int frameIndex, float scaleX = 1.0f, float scaleY = 1.0f) {
  int col = frameIndex % columns;
  int row = frameIndex / columns;

  SDL_FRect clip{(float)col * frameWidth, (float)row * frameHeight,
                 (float)frameWidth, (float)frameHeight};

  baseTexture->render(x, y, &clip, frameWidth * scaleX, frameHeight * scaleY);
}

void SpriteSheet::renderTile(float x, float y, int col, int row) {
  SDL_FRect clip{(float)col * frameWidth, (float)row * frameHeight,
                 (float)frameWidth, (float)frameHeight};

  baseTexture->render(x, y, &clip, frameWidth, frameHeight);
}