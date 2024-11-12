package main

import rl "vendor:raylib"

world: World
camera: rl.Camera2D

load_game :: proc() {
	bind_key("move_up", rl.KeyboardKey.W)
	bind_key("move_down", rl.KeyboardKey.S)
	bind_key("move_left", rl.KeyboardKey.A)
	bind_key("move_right", rl.KeyboardKey.D)

	add_texture("player")
	add_texture("world")

	world = World{}
	world.player = make_player({32, 32})

	camera.offset = {GAME_WIDTH / 2, GAME_HEIGHT / 2}
	camera.zoom = 4
	camera.target = world.player.pos
}

update_game :: proc(dt: f32) {
	update_world(&world)
	update_player(&world.player)
	camera.target = world.player.pos
}

draw_game :: proc() {
	rl.BeginMode2D(camera)
	draw_world(&world)
	rl.EndMode2D()
}

draw_ui_game :: proc() {

}

unload_game :: proc() {
	unload_assets()
}
