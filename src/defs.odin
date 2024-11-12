package main

DEBUG :: #config(DEBUG, false)
NAME :: #config(NAME, "")
ASSETS_PATH :: #config(ASSETS_PATH, "./assets")

GAME_WIDTH :: 1280
GAME_HEIGHT :: 720
SCREEN_WIDTH :: 1280
SCREEN_HEIGHT :: 720

Scene :: enum {
	MENU,
	GAME,
}
