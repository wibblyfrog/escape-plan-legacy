#include "world.h"

World::World() {
  for (int idx = 0; idx < WORLD_WIDTH * WORLD_HEIGHT; idx++) {
    tiles.push_back(Tile(3, false, 0));
    // Create random rocks
    if (GetRandomValue(0, 100) > 70) {
      tiles[idx] = Tile(1, true, 3);
    }
  }
}
World::~World() {}

Tile *World::GetTile(int x, int y) { return &tiles[CoordToIndex(x, y)]; }

void World::SetTile(int x, int y, Tile tile) {
  tiles[CoordToIndex(x, y)] = tile;
}

void World::SetTile(int idx, Tile tile) { tiles[idx] = tile; }

bool World::CheckCollision(int x, int y) {}

void World::DrawMap(Rectangle region) {
  for (int idx = 0; idx < WORLD_WIDTH * WORLD_HEIGHT; idx++) {
    Vector2 pos = {
        IndexToVector2(idx).x * CELL_SIZE,
        IndexToVector2(idx).y * CELL_SIZE,
    };
    if (CheckCollisionRecs(Rectangle{pos.x, pos.y, CELL_SIZE, CELL_SIZE},
                           region)) {
      DrawSprite(tiles[idx].index, pos);
    }
  }
}