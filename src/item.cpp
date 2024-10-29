#include "item.h"

void Item::Update(float dt, Vector2 target) {
  pos = Vector2Lerp(pos, target, 1.25 * dt);
}

void Item::Draw(Texture spritesheet) {
  DrawSprite(spritesheet, 8, pos.x, pos.y, 1.0f);
}