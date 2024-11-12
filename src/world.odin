package main

import rl "vendor:raylib"

World :: struct {
	width:   i32,
	height:  i32,
	player:  Player,
	tiles:   [dynamic]Tile,
	rocks:   map[i32]Rock,
	sprites: [dynamic]Sprite,
}

make_world :: proc() -> World {
	return World{width = WorldConfig.width, height = WorldConfig.height}
}

update_world :: proc(w: ^World) {
	using w
}

draw_world :: proc(w: ^World) {
	using w

	// Draw Y-Sorted sprites
	clear_dynamic_array(&world.sprites)
	append(&world.sprites, player.sprite)
	draw_sprites_ysort(world.sprites[:])
}

unload_world :: proc(w: ^World) {
	using w
	clear_dynamic_array(&sprites)
}
