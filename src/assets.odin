package main

import "core:fmt"
import rl "vendor:raylib"

AssetsType :: struct {
	textures: map[string]rl.Texture,
	sounds:   map[string]rl.Sound,
	music:    map[string]rl.Music,
}

make_assets :: proc() -> AssetsType {
	return AssetsType {	
		textures = make(map[string]rl.Texture),
		sounds = make(map[string]rl.Sound),
		music = make(map[string]rl.Music)
	}
}

add_texture :: proc(name: string) {
	Assets.textures[name] = rl.LoadTexture(fmt.caprintf("%s/images/%s.png", ASSETS_PATH, name))
}

get_texture :: proc(name: string) -> ^rl.Texture {
	return &Assets.textures[name]
}

unload_assets :: proc() {
	for key, texture in Assets.textures {
		rl.UnloadTexture(texture)
		delete_key(&Assets.textures, key)
	}

	for key, sound in Assets.sounds {
		rl.UnloadSound(sound)
		delete_key(&Assets.sounds, key)
	}

	for key, music in Assets.music {
		rl.UnloadMusicStream(music)
		delete_key(&Assets.music, key)
	}
}
