#pragma once

#include <raylib.h>

#include "utils.h"
#include "world.h"

struct Player {
  Vector2 pos;
  Vector2 vel;
  float speed = 25;

  void Update(World* world, float dt);
  void Draw(Texture2D spritesheet);
};