#pragma once

#include "common.h"
#include "utils.h"

enum ItemTypes { TETHER, PATCH, AMMO };

struct Droppod {
 public:
  Rectangle bounds = Rectangle{0, 0, 24, 8};

  Droppod();
  ~Droppod();

  void CraftItem();

  void Update();
  void Draw();
};