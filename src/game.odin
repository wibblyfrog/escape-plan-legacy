package main

import rl "vendor:raylib"

world: World

load_game :: proc() {
	bind_key("move_up", rl.KeyboardKey.W)
	bind_key("move_down", rl.KeyboardKey.S)
	bind_key("move_left", rl.KeyboardKey.A)
	bind_key("move_right", rl.KeyboardKey.D)

	add_texture("player")
	add_texture("world")

	world = make_world()
}

update_game :: proc(dt: f32) {

	if (rl.IsKeyPressed(.R) && DEBUG) {
		unload_world(&world)
		load_all_configs()
		world = make_world()
	}

	update_world(&world)
}

draw_game :: proc() {
	draw_world(&world)
}

draw_ui_game :: proc() {
	rl.DrawFPS(0, 0)
}

unload_game :: proc() {
	unload_assets()
}
