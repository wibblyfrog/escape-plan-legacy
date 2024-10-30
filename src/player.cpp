#include "player.h"

void Player::Update(World* world, float dt) {
  if (break_timer > 0) {
    break_timer -= dt;
  }

  if (IsKeyDown(KEY_W) && !world->IsSolid(pos.x, pos.y - 1) &&
      !world->IsSolid(pos.x + 7, pos.y - 1))
    pos.y -= 1;
  else if (IsKeyDown(KEY_S) && !world->IsSolid(pos.x, pos.y + 8) &&
           !world->IsSolid(pos.x + 7, pos.y + 8))
    pos.y += 1;
  if (IsKeyDown(KEY_A) && !world->IsSolid(pos.x - 1, pos.y) &&
      !world->IsSolid(pos.x - 1, pos.y + 7))
    pos.x -= 1;
  else if (IsKeyDown(KEY_D) && !world->IsSolid(pos.x + 8, pos.y) &&
           !world->IsSolid(pos.x + 8, pos.y + 7))
    pos.x += 1;
}

void Player::Draw(Texture2D spritesheet) {
  DrawSprite(spritesheet, 0, pos, 1.0);
  // DrawText("@", int(pos.x), int(pos.y), CELL_SIZE, YELLOW);
}