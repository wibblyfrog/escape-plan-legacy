#pragma once

#include <raylib.h>

#include "utils.h"
#include "world.h"

struct Player {
  Vector2 pos;
  Vector2 vel;
  float speed = 25;
  int hp = 0;
  int oxygen = 10;
  int carbon = 0;

  int break_dist = 14;
  float break_timer;
  float break_time = 0.2;

  void Update(World* world, float dt);
  void Draw(Texture2D spritesheet);
};