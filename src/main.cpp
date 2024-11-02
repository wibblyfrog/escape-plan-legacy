#include "common.h"
#include "game.h"
#include "game_over.h"
#include "game_won.h"
#include "menu.h"
#include "player.h"
#include <vector>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

enum GameState state = GameState::GAME;
Menu menu;
Game game;
GameOver game_over;
GameWon game_won;
Camera2D *game_camera;

void SetPlayerCanShoot(bool can_shoot)
{
  game.player.can_shoot = can_shoot;
}

void SpawnBullet(Vector2 pos, Vector2 dir, float angle)
{
  game.SpawnBullet(pos, dir, angle);
}

void ChangeState(enum GameState new_state)
{
  switch (state)
  {
  case MENU:
    menu.Unload();
    break;
  case GAME:
    game.Unload();
    break;
  case GAME_OVER:
    game_over.Unload();
    break;
  case GAME_WON:
    game_won.Unload();
    break;
  }

  state = new_state;
  switch (state)
  {
  case MENU:
    menu.Load();
    break;
  case GAME:
    game.Load();
    break;
  case GAME_OVER:
    game_over.Load();
    break;
  case GAME_WON:
    game_won.Load();
    break;
  }
}

static void UpdateDrawFrame()
{
  float dt = GetFrameTime();
  switch (state)
  {
  case MENU:
    menu.Update(dt);
    break;
  case GAME:
    game.Update(dt);
    break;
  case GAME_OVER:
    game_over.Update(dt);
    break;
  case GAME_WON:
    game_won.Update(dt);
    break;
  }

  BeginDrawing();
  ClearBackground(Color{15, 15, 15, 255});
  switch (state)
  {
  case MENU:
    menu.Draw();
    break;
  case GAME:
    game.Draw();
    break;
  case GAME_OVER:
    game_over.Draw();
    break;
  case GAME_WON:
    game_won.Draw();
    break;
  }
  EndDrawing();
}

int main(void)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Escape Plan");
  // GuiLoadStyle("resources/styles/amber/style_amber.rgs");
  SetTraceLogLevel(LOG_ALL);

  // Load();
  switch (state)
  {
  case MENU:
    menu.Load();
    break;
  case GAME:
    game.Load();
    break;
  case GAME_OVER:
    game_over.Load();
    break;
  case GAME_WON:
    game_won.Load();
    break;
  }

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    UpdateDrawFrame();
  }
#endif
  switch (state)
  {
  case MENU:
    menu.Unload();
    break;
  case GAME:
    game.Unload();
    break;
  case GAME_OVER:
    game_over.Unload();
    break;
  case GAME_WON:
    game_won.Unload();
    break;
  }
  CloseWindow();
  return 0;
}