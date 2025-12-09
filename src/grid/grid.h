#ifndef GRID_H
#define GRID_H
#pragma once

#include <memory>
#include <vector>

class Hitbox;
class Texture;

class Grid {
public:
  Grid(int cols, int rows, int tileW, int tileH);

  void setTile(int x, int y, Texture *texture, std::unique_ptr<Hitbox> hitbox);
  Texture *getTileTexture(int x, int y) const;
  Hitbox *getTileHitbox(int x, int y) const;

  const std::vector<std::unique_ptr<Hitbox>> &getHitboxes() const {
    return hitboxes;
  }

  void render(float scaleX, float scaleY) const;

private:
  int cols, rows;
  int tileW, tileH;
  std::vector<Texture *> tiles;
  std::vector<std::unique_ptr<Hitbox>> hitboxes;
};
#endif