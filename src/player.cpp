#include "player.h"

void Player::Update(float dt) {
  vel = Vector2{0, 0};
  if (IsKeyDown(KEY_W))
    vel.y = -1;
  else if (IsKeyDown(KEY_S))
    vel.y = 1;
  if (IsKeyDown(KEY_A))
    vel.x = -1;
  else if (IsKeyDown(KEY_D))
    vel.x = 1;

  pos.x += vel.x * speed * dt;
  pos.y += vel.y * speed * dt;
}

void Player::Draw(Texture2D spritesheet) { DrawSprite(spritesheet, 0, pos); }