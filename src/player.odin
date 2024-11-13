package main

import "core:math/linalg"
import rl "vendor:raylib"

PlayerConfigType :: struct {
	speed:           f32,
	animation_speed: f32,
}
PlayerConfig := PlayerConfigType{}

Player :: struct {
	pos:       rl.Vector2,
	vel:       rl.Vector2,
	speed:     f32,
	sprite:    AnimatedSprite,
	inventory: map[string]i32,
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
			0.1,
			{1, 2, 3, 4},
			{0, 4},
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
		// sprite.flip_h = -1
	} else if is_key_down("move_right") {
		vel.x = 1
		// sprite.flip_h = 1
	}
	vel = rl.Vector2Normalize(vel)
	if rl.IsKeyDown(.LEFT_SHIFT) {
		sprite.animation_speed = 0.075
		pos += vel * (speed * 1.5) * rl.GetFrameTime()
	} else {
		sprite.animation_speed = 0.1
		pos += vel * speed * rl.GetFrameTime()
	}

	sprite.dest.x = pos.x
	sprite.dest.y = pos.y

	angle: f32 =
		linalg.atan2(f32(rl.GetMouseY() - (GAME_HEIGHT / 2)), f32(rl.GetMouseX() - (GAME_WIDTH / 2))) *
		(180.0 / linalg.PI)
	sprite.flip_h = 1
	if linalg.abs(angle) > 90 {
		sprite.flip_h = -1
	}

	if vel != 0 {
		update_asprite(&sprite)
	} else {
		sprite.src = {0, 0, 8, 8}
	}
}
