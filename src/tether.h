#pragma once

#include "common.h"
#include "utils.h"

struct Tether
{
  Vector2 pos;
  float range = 80;
  bool is_connected = false;
};