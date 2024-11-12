package main

import rl "vendor:raylib"

load_menu :: proc() {}

update_menu :: proc(dt: f32) {}

draw_menu :: proc() {}

draw_ui_menu :: proc() {
	rl.ClearBackground(rl.Color{15, 15, 15, 255})

	rl.DrawText(NAME, 4, 4, 30, rl.WHITE)
	if (rl.GuiButton({4, 40, 64, 24}, "Play")) {
		change_scene(.GAME)
	}
	if (rl.GuiButton({4, 82, 64, 24}, "Quit")) {
		quit_game()
	}

}

unload_menu :: proc() {}
