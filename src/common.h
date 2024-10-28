#pragma once

#include <raylib.h>
#include <raymath.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

const int SCREEN_WIDTH = 1270;
const int SCREEN_HEIGHT = 720;
const int GAME_WIDTH = 240;
const int GAME_HEIGHT = 126;
const int WORLD_WIDTH = 100;
const int WORLD_HEIGHT = 100;
const int SPRITESHEET_WIDTH = 8;
const int SPRITESHEET_HEIGHT = 8;
const int CELL_SIZE = 8;

extern Camera2D camera;
extern Texture2D spritesheet;
extern Player player;
extern World world;