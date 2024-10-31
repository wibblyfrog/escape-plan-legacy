#include <vector>

#include "common.h"
#include "droppod.h"
#include "item.h"
#include "player.h"
#include "tether.h"
#include "texture_button.h"
#include "world.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

Camera2D camera;
Camera2D ui_camera;
Texture2D spritesheet;
World world;
Player player;
Droppod pod;
Vector2 mouse_pos;

// std::vector<Vector2> oxygen_sources;
std::vector<Tether> tethers;

static void Load() {
  camera = Camera2D{};
  camera.offset = Vector2{GAME_WIDTH / 2, GAME_HEIGHT / 2};

  ui_camera = Camera2D{};

  spritesheet = LoadTexture("resources/spritesheet.png");
  SetTextureFilter(spritesheet, TEXTURE_FILTER_POINT);
  world = World();

  player = Player();
  //* Place player in the center of the world
  player.pos = Vector2{float(world.GetCenter().x) * CELL_SIZE,
                       float(world.GetCenter().y * CELL_SIZE)};
  pod.pos = Vector2{player.pos.x - 24, player.pos.y};
  pod.bounds.x = pod.pos.x;
  pod.bounds.y = pod.pos.y;

  tethers.push_back(Tether(Vector2{pod.pos.x + 12, pod.pos.y + 4}));
  tethers.back().is_connected = true;
}

static void Update(float dt) {
  //* Maintain vertical size
  camera.offset = Vector2{(SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2)};
  camera.zoom = float(SCREEN_HEIGHT) / float(GAME_HEIGHT);
  ui_camera.zoom = float(SCREEN_HEIGHT) / float(GAME_HEIGHT);
  player.Update(&world, dt);

  // Check item collision with player
  for (auto it = world.items.begin(); it != world.items.end();) {
    if (player.carbon < player.max_carbon) {
      (*it).Update(dt, player.pos);
    } else {
      break;
    }

    if (CheckCollisionCircles((*it).pos, 2, player.pos, 2)) {
      it = world.items.erase(it);
      player.carbon++;
    } else {
      ++it;
    }
  }

  // Show crafting panel
  if (CheckCollisionRecs(
          Rectangle{player.pos.x, player.pos.y, CELL_SIZE, CELL_SIZE},
          Rectangle{pod.pos.x - 4, pod.pos.y - 4, 36, 22})) {
    pod.showInfoPanel = true;
  } else {
    pod.showInfoPanel = false;
  }

  camera.target = Vector2Add(player.pos, Vector2(4, 4));

  // Do damage to clicked rocks
  mouse_pos = GetScreenToWorld2D(GetMousePosition(), camera);
  Vector2 mouse_world_pos = Vector2{float(int(mouse_pos.x / CELL_SIZE)),
                                    float(int(mouse_pos.y / CELL_SIZE))};
  if (world.GetTile(mouse_world_pos.x, mouse_world_pos.y)->isRock &&
      IsMouseButtonDown(MOUSE_BUTTON_LEFT) &&
      Vector2Distance(
          Vector2{mouse_world_pos.x * CELL_SIZE, mouse_world_pos.y * CELL_SIZE},
          player.pos) <= player.break_dist) {
    if (player.break_timer <= 0) {
      world.DamageTile(mouse_world_pos.x, mouse_world_pos.y, 1);
      player.break_timer = player.break_time;
    }
  }

  // Place tether on right-click if near another tether
  if (player.tethers > 0 && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    bool can_place = false;
    for (auto tether : tethers) {
      if (CheckCollisionPointCircle(
              Vector2{float(mouse_world_pos.x * CELL_SIZE) + 4,
                      float(mouse_world_pos.y * CELL_SIZE) + 4},
              tether.pos, tether.range)) {
        can_place = true;
      }
    }

    if (can_place == true) {
      tethers.push_back(
          Tether(Vector2{float(mouse_world_pos.x * CELL_SIZE) + 4,
                         float(mouse_world_pos.y * CELL_SIZE) + 4}));
      player.tethers -= 1;
    }
  }
}

static void Draw() {
  BeginMode2D(camera);

  world.DrawMap(spritesheet, Rectangle{camera.target.x - (GAME_WIDTH / 2),
                                       camera.target.y - (GAME_HEIGHT / 2),
                                       GAME_WIDTH, GAME_HEIGHT});
  // Draw Player shadow
  DrawCircleV(Vector2Add(player.pos, Vector2{4, 7}), 3, Color{15, 15, 15, 100});

  for (int i = 0; i < tethers.size(); i++) {
    Tether& tether = tethers[i];

    if (CheckCollisionPointCircle(player.pos, tether.pos, tether.range)) {
      DrawLineEx(tether.pos, Vector2{player.pos.x + 4, player.pos.y + 4}, 1.0f,
                 BLUE);
    }

    for (int i = 0; i < tethers.size(); i++) {
      Tether& prev = tethers[i - 1];
      if (CheckCollisionPointCircle(prev.pos, tether.pos, tether.range)) {
        DrawLineEx(tether.pos, prev.pos, 2.0f, BLUE);
      }
    }
    // DrawLineEx(tether.pos, prev.pos, 2.0f, BLUE);
    DrawSprite(spritesheet, 12, tether.pos.x - 4, tether.pos.y - 4, 1.0f,
               WHITE);
  }

  player.Draw(spritesheet);

  // Droppod drawing routines
  pod.Draw(spritesheet);

  EndMode2D();

  GuiPanel(Rectangle{2, 2, 128, 66}, "Status");
  GuiLabel(Rectangle{4, 16, 128, 32},
           TextFormat("Suit Damage: %i", 100.0f - player.hp / player.max_hp));
  GuiLabel(Rectangle{4, 30, 128, 32}, TextFormat("Carbon: %i", player.carbon));
  GuiLabel(Rectangle{4, 44, 128, 32},
           TextFormat("Tethers: %i", player.tethers));

  if (pod.showInfoPanel) {
    GuiPanel(Rectangle{2, 70, 128, 72}, "Drop Pod");
    GuiLabel(Rectangle{4, 100, 128, 14},
             TextFormat("Shuttle Arrival: %i", pod.days_left));
    GuiLabel(Rectangle{4, 116, 128, 14},
             TextFormat("Stored Carbon: %i", pod.carbon));
    if (GuiButton(Rectangle{4, 132, 48, 20}, "Craft")) {
      pod.showCraftingPanel = true;
    }

    if (GuiButton(Rectangle{54, 132, 48, 20}, "Deposit Carbon")) {
      pod.carbon += player.carbon;
      player.carbon = 0;
    }

    if (pod.showCraftingPanel) {
      int result =
          GuiWindowBox(Rectangle{2, SCREEN_HEIGHT - (SCREEN_HEIGHT / 2), 128,
                                 (SCREEN_HEIGHT / 2) - 2},
                       "Crafting");

      if (TextureButton(spritesheet, 12, Rectangle{4, 252, 32, 32},
                        "Tether\n(-10 C)")) {
        if (pod.carbon >= 10) {
          pod.carbon -= 10;
          player.tethers += 1;
        }
      }

      if (result > 0) {
        pod.showCraftingPanel = false;
      }
    }
  }

  if (GuiButton(Rectangle{SCREEN_WIDTH - 64, 0, 64, 20}, "Fill carbon")) {
    player.carbon = player.max_carbon;
  }
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
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Escape Plan");
  // GuiLoadStyle("resources/styles/amber/style_amber.rgs");
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