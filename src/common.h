#pragma once

#include <raylib.h>
#include <raymath.h>

#include <map>
#include <vector>

#define RAYGUI_IMPLEMENTATION
// #define RAYGUI_STANDALONE
#include "raygui.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

const int SCREEN_WIDTH = 1270;
const int SCREEN_HEIGHT = 720;
const int GAME_WIDTH = 240;
const int GAME_HEIGHT = 126;

extern Camera2D camera;