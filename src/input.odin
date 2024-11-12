package main

import rl "vendor:raylib"

bind_key :: proc(name: string, key: rl.KeyboardKey) {
	SettingsConfig.keys[name] = key
}

is_key_down :: proc(key: string) -> bool {
	return rl.IsKeyDown(SettingsConfig.keys[key])
}

is_key_pressed :: proc(key: string, repeat: bool = false) -> bool {
	if repeat {
		return rl.IsKeyPressed(SettingsConfig.keys[key]) || rl.IsKeyPressedRepeat(SettingsConfig.keys[key])
	}
	return rl.IsKeyPressed(SettingsConfig.keys[key])
}

is_key_released :: proc(key: string) -> bool {
	return rl.IsKeyReleased(SettingsConfig.keys[key])
}
