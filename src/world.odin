package main

import rl "vendor:raylib"

WorldConfigType :: struct {
	width:  i32,
	height: i32,
}
WorldConfig := WorldConfigType{}

World :: struct {
	width:   i32,
	height:  i32,
	camera:  rl.Camera2D,
	player:  Player,
	tiles:   [dynamic]Tile,
	rocks:   map[i32]Rock,
	sprites: [dynamic]Sprite,
}

make_world :: proc() -> World {
	w := World {
		width  = WorldConfig.width,
		height = WorldConfig.height,
	}

	create_tilemap(&w)
	w.player = make_player({f32(w.width / 2) * 8, f32(w.height / 2) * 8})

	w.camera.offset = rl.Vector2{GAME_WIDTH / 2, GAME_HEIGHT / 2}
	w.camera.zoom = 4
	w.camera.target = w.player.pos

	return w
}

create_tilemap :: proc(w: ^World) {
	using w

	// Reset containers
	clear_dynamic_array(&tiles)
	clear_map(&rocks)

	// Fill tilemap
	for y: i32; y < height; y += 1 {
		for x: i32; x < width; x += 1 {
			t: Tile = {}
			t.id = 0

			// Put walls along boundary
			if x == 0 || y == 0 || x == width - 1 || y == height - 1 {
				t.id = 1
				t.solid = true
			} else {

				// Place random rocks
				rock_type := get_weighted_rock()
				if rock_type != "empty" &&
				   rl.Vector2Distance({f32(x), f32(y)}, {f32(width / 2), f32(height / 2)}) > 6 {
					rocks[y * width + x] = make_rock(rock_type, {x, y})
				}
			}
			append(&tiles, t)
		}
	}
}

update_world :: proc(w: ^World) {
	using w

	update_player(&player)
	camera.target = player.pos

	for key, &rock in rocks {
		rock.sprite.src.x = (f32(TileConfig.rocks[rock.type].sprite % 8) * 8) + (f32(rock.hp - 1) * 8)
	}
}

draw_world :: proc(w: ^World) {
	using w

	rl.BeginMode2D(camera)
	defer rl.EndMode2D()

	// Draw tilemap
	for y: i32 = i32(player.pos.y / 8) - 15; y < i32(player.pos.y / 8) + 15; y += 1 {
		for x: i32 = i32(player.pos.x / 8) - 25; x < i32(player.pos.x) / 8 + 25; x += 1 {
			if x < 0 || y < 0 || x >= width || y >= height {continue}
			tile: ^Tile = &tiles[y * width + x]
			rl.DrawTexturePro(
				get_texture("world")^,
				{f32(tile.id % width) * 8, f32(tile.id / width) * 8, 8, 8},
				{f32(x) * 8, f32(y) * 8, 8, 8},
				{0, 0},
				0.0,
				rl.WHITE,
			)
		}
	}

	// Draw player shadow
	rl.DrawEllipse(i32(player.pos.x), i32(player.pos.y + 4), 4, 2, rl.Color{0, 0, 0, 80})

	// Draw Y-Sorted sprites
	clear_dynamic_array(&sprites)
	append(&sprites, player.sprite)
	for key, rock in rocks {
		append(&sprites, rock.sprite)
	}

	region: rl.Rectangle = {
		camera.target.x - camera.offset.x,
		camera.target.y - camera.offset.y,
		GAME_WIDTH,
		GAME_HEIGHT,
	}
	draw_sprites_ysort(region, sprites[:])
}

unload_world :: proc(w: ^World) {
	using w
	clear_dynamic_array(&sprites)
	clear_dynamic_array(&tiles)
	clear_map(&rocks)
}
