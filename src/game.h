#pragma once

#include "common.h"
#include "droppod.h"
#include "item.h"
#include "player.h"
#include "squib.h"
#include "tether.h"
#include "texture_button.h"
#include "utils.h"
#include "world.h"

struct Bullet
{
  Vector2 pos;
  Vector2 dir;
  float angle;
  float lifetime = 1.0;
  bool alive = true;
};

struct Game
{
  Camera2D camera;
  Camera2D ui_camera;
  Texture2D spritesheet;
  World world;
  Player player;
  Droppod pod;
  Vector2 mouse_pos;
  std::vector<Bullet> bullets;
  std::vector<Tether> tethers;
  std::vector<Squib> squibs;
  Vector2 pickup_pos;
  bool paused = false;

  void SpawnBullet(Vector2 pos, Vector2 dir, float angle);

  void Load();
  void Update(float dt);
  void Draw();
  void Unload();
};