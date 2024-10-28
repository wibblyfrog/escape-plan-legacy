#pragma once

#include <map>
#include <vector>

#include "common.h"
#include "utils.h"

struct Tile {
  int index;
  bool isSolid;
  int health;

  Tile(int index = 3, bool isSolid = false, int health = 0)
      : index(index), isSolid(isSolid), health(health) {}
};

struct World {
  std::vector<Tile> tiles;

  World();
  ~World();

  Tile *GetTile(int x, int y);
  void SetTile(int x, int y, Tile tile);
  void SetTile(int idx, Tile tile);

  bool CheckCollision(int x, int y);

  void DrawMap(Rectangle region);
};