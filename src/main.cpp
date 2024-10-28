#include "common.h"
#include "player.h"
#include "utils.h"
#include "world.h"

Camera2D camera;
Texture2D spritesheet;
World world;

static void Load() {
  camera = Camera2D{};
  camera.offset = Vector2{GAME_WIDTH / 2, GAME_HEIGHT / 2};
  spritesheet = LoadTexture("resources/spritesheet.png");
  world = World();

  player = Player();
}

static void Update(float dt) {
  // Maintain vertical size
  camera.offset = Vector2{GAME_WIDTH / 2, GAME_HEIGHT / 2};
  camera.zoom = float(SCREEN_HEIGHT) / float(GAME_HEIGHT);

  player.Update(dt);
  camera.target = player.pos;
}

static void Draw() {
  BeginMode2D(camera);
  world.DrawMap(Rectangle{0, 0, GAME_WIDTH, GAME_HEIGHT});
  player.Draw();
  EndMode2D();
  DrawFPS(0, 0);
}
static void Unload() { UnloadTexture(spritesheet); }

static void UpdateDrawFrame() {
  float dt = GetFrameTime();
  Update(dt);
  BeginDrawing();
  ClearBackground(Color{15, 15, 15, 255});
  Draw();
  EndDrawing();
}

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib game template");
  Load();

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }
#endif
  Unload();
  CloseWindow();
  return 0;
}