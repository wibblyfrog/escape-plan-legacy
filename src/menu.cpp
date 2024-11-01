#include "menu.h"

void Menu::Load() {}

void Menu::Update(float dt) {}

void Menu::Draw()
{
  DrawText("Escape Plan", 8, 8, 64, WHITE);
  if (GuiButton(Rectangle{4, 72, 128, 48}, "Start Game"))
  {
    ChangeState(GameState::GAME);
  }
}

void Menu::Unload() {}