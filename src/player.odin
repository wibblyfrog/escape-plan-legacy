package main

import "core:math/linalg"
import rl "vendor:raylib"

Player :: struct {
	pos:    rl.Vector2,
	vel:    rl.Vector2,
	speed:  f32,
	sprite: AnimatedSprite,
}

make_player :: proc(set_pos: [2]f32) -> Player {
	return Player {
		pos = set_pos,
		speed = PlayerConfig.speed,
		sprite = make_asprite(
			"player",
			{0, 0, 8, 8},
			{set_pos.x, set_pos.y, 8, 8},
			{4, 4},
			8,
			PlayerConfig.animation_speed,
			{1, 2, 3, 4},
			{4, 4},
		),
	}
}

update_player :: proc(p: ^Player) {
	using p

	vel = 0

	if is_key_down("move_up") {
		vel.y = -1
	} else if is_key_down("move_down") {
		vel.y = 1
	}
	if is_key_down("move_left") {
		vel.x = -1
		sprite.flip_h = -1
	} else if is_key_down("move_right") {
		vel.x = 1
		sprite.flip_h = 1
	}
	vel = rl.Vector2Normalize(vel)

	pos += vel * speed * rl.GetFrameTime()

	sprite.dest.x = pos.x
	sprite.dest.y = pos.y

	if vel != 0 {
		update_asprite(&sprite)
	} else {
		sprite.src = {0, 0, 8, 8}
	}
}
