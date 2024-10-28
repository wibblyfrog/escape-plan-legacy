#include "world.h"

World::World() {
  for (int idx = 0; idx < WORLD_WIDTH * WORLD_HEIGHT; idx++) {
    tiles.push_back(Tile(3, false, 0, false));
    // Create random rocks
    if (GetRandomValue(0, 100) > 70) {
      tiles[idx] = Tile(1, true, 3, true);
    }
  }
}
World::~World() {}

Tile* World::GetTile(int x, int y) { return &tiles[CoordToIndex(x, y)]; }

void World::SetTile(int x, int y, Tile tile) {
  tiles[CoordToIndex(x, y)] = tile;
}

void World::SetTile(int idx, Tile tile) { tiles[idx] = tile; }

void World::DamageTile(int x, int y, int amount) {
  Tile* tile = GetTile(x, y);
  if (tile->isRock) {
    tile->health -= amount;
  }

  if (tile->health <= 0) {
    tiles[CoordToIndex(x, y)] = Tile(3, false, 0, false);
  }
}

bool World::IsSolid(int x, int y) {
  x = int(x / CELL_SIZE);
  y = int(y / CELL_SIZE);
  if (x < 0 || x > WORLD_WIDTH || y < 0 || y > WORLD_HEIGHT) return true;
  if (tiles[CoordToIndex(x, y)].isSolid) return true;
  return false;
}

void World::DrawMap(Texture2D spritesheet, Rectangle region) {
  for (int idx = 0; idx < WORLD_WIDTH * WORLD_HEIGHT; idx++) {
    Vector2 pos = {
        float(IndexToVector2(idx).x) * CELL_SIZE,
        float(IndexToVector2(idx).y) * CELL_SIZE,
    };
    // Need to do this better, rather than checking EVERY world tile, should
    // just check only the tiles in the region
    if (CheckCollisionRecs(Rectangle{pos.x, pos.y, CELL_SIZE, CELL_SIZE},
                           region)) {
      DrawSprite(spritesheet, tiles[idx].index, pos);
    }
  }
}