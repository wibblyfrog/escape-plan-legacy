package main

import "core:slice"
import rl "vendor:raylib"

Sprite :: struct {
	texture: string,
	src:     rl.Rectangle,
	dest:    rl.Rectangle,
	origin:  rl.Vector2,
	angle:   f32,
	flip_h:  f32,
	tint:    rl.Color,
	y_sort:  rl.Vector2,
}

AnimatedSprite :: struct {
	using sprite:    Sprite,
	cell_size:       f32,
	animation_speed: f32,
	frames:          []i32,
	frame:           i32,
	frame_timer:     f32,
}

make_sprite :: proc(
	set_texture: string,
	set_src, set_dest: rl.Rectangle,
	set_origin: [2]f32,
	set_ysort: [2]f32 = {0, 0},
) -> Sprite {
	return Sprite {
		texture = set_texture,
		src = set_src,
		dest = set_dest,
		origin = set_origin,
		angle = 0.0,
		flip_h = 1,
		tint = rl.WHITE,
		y_sort = set_ysort,
	}
}

make_asprite :: proc(
	set_texture: string,
	set_src, set_dest: rl.Rectangle,
	set_origin: [2]f32,
	set_cell_size: f32,
	set_animation_speed: f32,
	set_frames: []i32,
	set_ysort: [2]f32 = {0, 0},
) -> AnimatedSprite {
	return AnimatedSprite {
		texture = set_texture,
		src = set_src,
		dest = set_dest,
		origin = set_origin,
		angle = 0.0,
		flip_h = 1,
		tint = rl.WHITE,
		y_sort = set_ysort,
		cell_size = set_cell_size,
		animation_speed = set_animation_speed,
		frames = set_frames,
		frame = 0,
		frame_timer = 0,
	}
}

draw_sprite :: proc(sprite: ^Sprite) {
	using sprite
	rl.DrawTexturePro(get_texture(texture)^, {src.x, src.y, src.width * flip_h, src.height}, dest, origin, angle, tint)
}

draw_sprites_ysort :: proc(sprites: []Sprite) {
	slice.sort_by(sprites, proc(a: Sprite, b: Sprite) -> bool {
		return (a.dest.y + a.origin.y) < (b.dest.y + b.origin.y)
	})

	for &sprite in sprites {
		draw_sprite(&sprite)
	}
}

update_asprite :: proc(sprite: ^AnimatedSprite) {
	using sprite

	if frame_timer > animation_speed {
		frame_timer = 0
		frame += 1
	}

	src.x = f32(frame % i32(len(frames)) - 1) * cell_size
	frame_timer += rl.GetFrameTime()
}
