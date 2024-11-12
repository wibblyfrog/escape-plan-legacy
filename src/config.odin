package main

import "core:encoding/json"
import "core:fmt"
import "core:os"
import rl "vendor:raylib"

SettingsConfigType :: struct {
	window: struct {
		width:      i32,
		height:     i32,
		fullscreen: bool,
	},
	keys:   map[string]rl.KeyboardKey,
}
SettingsConfig := SettingsConfigType{}

WorldConfigType :: struct {
	width:  i32,
	height: i32,
}
WorldConfig := WorldConfigType{}

PlayerConfigType :: struct {
	speed:           f32,
	animation_speed: f32,
}
PlayerConfig := PlayerConfigType{}

TileConfigType :: struct {}
TileConfig := TileConfigType{}

ItemConfigType :: struct {}
ItemConfig := ItemConfigType{}

WeaponConfigType :: struct {}
WeaponConfig := WeaponConfigType{}

@(private = "file")
read_json_data :: proc(out: ^$T, $path: string) {
	file_path: string = fmt.aprintf("%s/data/%s.json", ASSETS_PATH, path)
	if file_data, ok := os.read_entire_file(file_path, allocator = context.temp_allocator); ok {
		// fmt.printfln("Successfully read file '%s'", path)
		if json.unmarshal(file_data, out) == nil {
			// fmt.printfln("Loaded '%s'", path)
		}
	} else {
		fmt.eprintfln("Failed to read file '%s'", path)
		// TODO: Create default config for type if not found
	}
}

load_settings_config :: proc() {
	read_json_data(&SettingsConfig, "settings")
}

load_world_config :: proc() {
	read_json_data(&WorldConfig, "world")
}

load_player_config :: proc() {
	read_json_data(&PlayerConfig, "player")
}

load_tile_config :: proc() {
	read_json_data(&TileConfig, "tiles")
}

load_item_config :: proc() {
	read_json_data(&ItemConfig, "items")
}

load_weapon_config :: proc() {
	read_json_data(&WeaponConfig, "weapons")
}

load_all_configs :: proc() {
	load_settings_config()
	load_world_config()
	load_player_config()
	load_tile_config()
	load_item_config()
	load_weapon_config()
}
