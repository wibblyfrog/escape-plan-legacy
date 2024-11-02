#include "player.h"

void Player::Update(World *world, float dt)
{
  if (break_timer > 0)
  {
    break_timer -= dt;
  }

  if (connected_to_tether == false && timer > 0)
  {
    timer -= dt;
  }
  else if (connected_to_tether == false && timer <= 0)
  {
    hp -= 1;
    timer = timer_max;
  }
  else if (connected_to_tether)
  {
    timer += 2 * dt;
  }
  timer = Clamp(timer, 0, timer_max);

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

  hp = Clamp(hp, 0, max_hp);

  // Shoot bullet
  float angle = atan2(GetMouseY() - (SCREEN_HEIGHT / 2), GetMouseX() - (SCREEN_WIDTH / 2)) * (180.0f / PI);
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
  {
    // TraceLog(LOG_DEBUG, "Shoot bullet");
    TraceLog(LOG_DEBUG, TextFormat("%f, %f", cos(angle) * dt, sin(angle) * dt));
    SpawnBullet(Vector2Add(Vector2{pos.x + 4, pos.y + 4}, Vector2{float(cos(angle)), float(sin(angle))}), angle);
  }
}

void Player::Draw(Texture2D spritesheet)
{
  DrawSprite(spritesheet, 0, pos, 1.0);
  // DrawSprite(spritesheet, 7, Vector2{pos.x + 4, pos.y + 4}, 1.0f, WHITE);

  // Flip gun if past angle
  float angle = atan2(GetMouseY() - (SCREEN_HEIGHT / 2), GetMouseX() - (SCREEN_WIDTH / 2)) * (180.0f / PI);
  float flip = 1;
  if (abs(angle) > 90)
  {
    flip = -1;
  }

  // Draw Gun
  DrawTexturePro(
      spritesheet,
      Rectangle{7 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE * flip},
      Rectangle{pos.x + 4, pos.y + 4, CELL_SIZE, CELL_SIZE},
      Vector2{-1, 4},
      angle,
      WHITE);
}