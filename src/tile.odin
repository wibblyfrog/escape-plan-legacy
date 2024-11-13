package main

import rl "vendor:raylib"

TileConfigType :: struct {
	empty_spawn_chance: i32,
	rocks:              map[string]struct {
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

get_weighted_rock :: proc() -> string {
	sum_of_weights: i32 = TileConfig.empty_spawn_chance
	for _, config in TileConfig.rocks {
		sum_of_weights += config.spawn_chance
	}

	rand: i32 = i32(rl.GetRandomValue(0, sum_of_weights))
	for key, config in TileConfig.rocks {
		if rand < config.spawn_chance {
			return key
		}
		rand -= config.spawn_chance
	}
	return "empty"
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
