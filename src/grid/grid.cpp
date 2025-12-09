#include "grid.h"
#include "../texture/texture.h"
#include "../physics/hitbox.h"

Grid::Grid(int cols, int rows, int tileW, int tileH)
    : cols(cols), rows(rows), tileW(tileW), tileH(tileH) {
  tiles.resize(cols * rows, nullptr);
}

void Grid::setTile(int x, int y, Texture* texture, std::unique_ptr<Hitbox> hitbox) {
  if (x < 0 || x >= cols || y < 0 || y >= rows) {
    return;
  }

  int index = y * cols + x;
  tiles[index] = texture;
  
  if (hitbox) {
    hitboxes.push_back(std::move(hitbox));
  }
}

Texture* Grid::getTileTexture(int x, int y) const {
  if (x < 0 || x >= cols || y < 0 || y >= rows) {
    return nullptr;
  }

  int index = y * cols + x;
  return tiles[index];
}

Hitbox* Grid::getTileHitbox(int x, int y) const {
  if (x < 0 || x >= cols || y < 0 || y >= rows) {
    return nullptr;
  }

  int index = y * cols + x;
  
  if (index < static_cast<int>(hitboxes.size())) {
    return hitboxes[index].get();
  }
  
  return nullptr;
}

void Grid::render(float scaleX, float scaleY) const {
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      int index = row * cols + col;
      Texture* texture = tiles[index];
      
      if (texture) {
        float x = col * tileW;
        float y = row * tileH;
        texture->render(x, y, scaleX, scaleY);
      }
    }
  }
}
