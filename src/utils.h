#pragma once

#include "common.h"

struct Vector2i {
  int x;
  int y;
};

int CoordToIndex(int x, int y);
Vector2 IndexToVector2(int index);
Vector2i IndexToVector2i(int index);

void DrawSprite(int index, Vector2 pos);
void DrawSprite(int index, Vector2i pos);
void DrawSprite(int index, int x, int y);