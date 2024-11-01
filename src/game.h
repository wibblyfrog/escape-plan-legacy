#pragma once

#include "common.h"
#include "droppod.h"
#include "item.h"
#include "player.h"
#include "tether.h"
#include "texture_button.h"
#include "utils.h"
#include "world.h"

struct Game
{
  Camera2D camera;
  Camera2D ui_camera;
  Texture2D spritesheet;
  World world;
  Player player;
  Droppod pod;
  Vector2 mouse_pos;
  bool paused = false;

  std::vector<Tether> tethers;
  void Load();
  void Update(float dt);
  void Draw();
  void Unload();
};