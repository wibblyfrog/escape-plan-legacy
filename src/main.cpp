#include "common.h"

Camera2D camera;

static void Load() {
  camera = Camera2D{};
  camera.offset = Vector2{GAME_WIDTH / 2, GAME_HEIGHT / 2};
}

static void Update(float dt) {
  // Maintain vertical size
  camera.offset = Vector2{GAME_WIDTH / 2, GAME_HEIGHT / 2};
  camera.zoom = float(SCREEN_HEIGHT) / float(GAME_HEIGHT);
}

static void Draw() { DrawFPS(0, 0); }
static void Unload() {}

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