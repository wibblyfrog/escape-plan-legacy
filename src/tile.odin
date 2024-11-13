package main

import rl "vendor:raylib"

TileConfigType :: struct {
	rocks: map[string]struct {
		texture:      string,
		sprite:       i32,
		hp:           i32,
		stack_size:   i32,
		drop_amount:  i32,
		spawn_chance: i32,
	},
}
TileConfig := TileConfigType{}

Tile :: struct {
	id:    i32,
	solid: bool,
}

Rock :: struct {
	type:   string,
	hp:     i32,
	sprite: Sprite,
}

make_rock :: proc(type: string, pos: [2]i32) -> Rock {
	proto := TileConfig.rocks[type]
	return Rock {
		type = type,
		hp = proto.hp,
		sprite = make_sprite(
			proto.texture,
			{f32(proto.sprite % 8) * 8, f32(proto.sprite / 8) * 8, 8, 8},
			{f32(pos.x) * 8, f32(pos.y) * 8, 8, 8},
			{0, 0},
			{0, 8},
		),
	}
}
