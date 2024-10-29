#include <vector>

#include "common.h"
#include "item.h"
#include "player.h"
#include "world.h"

Camera2D camera;
Camera2D ui_camera;
Texture2D spritesheet;
World world;
Player player;
Vector2 mouse_pos;

static void Load() {
  camera = Camera2D{};
  camera.offset = Vector2{GAME_WIDTH / 2, GAME_HEIGHT / 2};

  ui_camera = Camera2D{};

  spritesheet = LoadTexture("resources/spritesheet.png");
  SetTextureFilter(spritesheet, TEXTURE_FILTER_POINT);
  world = World();

  player = Player();
  //* Place player in the center of the world, removing any rocks that are there
  player.pos = Vector2{float(world.GetCenter().x) * CELL_SIZE,
                       float(world.GetCenter().y * CELL_SIZE)};
}

static void Update(float dt) {
  //* Maintain vertical size
  camera.offset = Vector2{(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2)};
  camera.zoom = float(SCREEN_HEIGHT) / float(GAME_HEIGHT);
  ui_camera.zoom = float(SCREEN_HEIGHT) / float(GAME_HEIGHT);
  player.Update(&world, dt);

  for (auto it = world.items.begin(); it != world.items.end();) {
    (*it).Update(dt, player.pos);

    if (CheckCollisionCircles((*it).pos, 2, player.pos, 2)) {
      it = world.items.erase(it);
      player.carbon++;
    } else {
      ++it;
    }
  }

  camera.target = Vector2Add(player.pos, Vector2(4, 4));

  mouse_pos = GetScreenToWorld2D(GetMousePosition(), camera);

  // Do damage to clicked rocks
  Vector2i mouse_world_pos =
      Vector2i{int(mouse_pos.x / CELL_SIZE), int(mouse_pos.y / CELL_SIZE)};
  if (world.GetTile(mouse_world_pos.x, mouse_world_pos.y)->isRock &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    world.DamageTile(mouse_world_pos.x, mouse_world_pos.y, 1);
  }
}

static void Draw() {
  BeginMode2D(camera);
  world.DrawMap(spritesheet, Rectangle{camera.target.x - (GAME_WIDTH / 2),
                                       camera.target.y - (GAME_HEIGHT / 2),
                                       GAME_WIDTH, GAME_HEIGHT});
  player.Draw(spritesheet);
  EndMode2D();

  BeginMode2D(ui_camera);
  DrawCircle(0, GAME_HEIGHT, 17, WHITE);
  DrawCircle(0, GAME_HEIGHT, 16, BLACK);
  DrawText(TextFormat("%i", player.carbon), 2, GAME_HEIGHT - 10, 8, WHITE);
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
  SetTraceLogLevel(LOG_ALL);
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