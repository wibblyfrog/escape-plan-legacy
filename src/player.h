#pragma once

#include "common.h"
#include "utils.h"

struct Player {
  Vector2 pos;
  Vector2i grid_pos;
  Vector2 vel;
  float speed;

  void Update(float dt);
  void Draw();
};