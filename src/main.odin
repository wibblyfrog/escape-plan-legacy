package main

import "core:fmt"
import rl "vendor:raylib"

@(private = "file")
current_scene: Scene = .GAME

@(private = "file")
running: bool = true

quit_game :: proc() {
	running = false
}

Assets: AssetsType

toggle_fullscreen :: proc() {
	rl.ToggleBorderlessWindowed()
	if (SettingsConfig.window.fullscreen) {
		rl.SetWindowSize(SettingsConfig.window.width, SettingsConfig.window.height)
		SettingsConfig.window.fullscreen = false
	} else {
		// rl.SetWindowSize(rl.GetMonitorWidth(0), rl.GetMonitorHeight(0))
		rl.MaximizeWindow()
		SettingsConfig.window.fullscreen = true
	}
}

change_scene :: proc(new_scene: Scene) {
	switch (current_scene) {
	case .MENU:
		unload_menu()
	case .GAME:
		unload_game()
	}

	current_scene = new_scene
	switch (current_scene) {
	case .MENU:
		load_menu()
	case .GAME:
		load_menu()
	}
}

main :: proc() {
	load_all_configs()
	rl.SetConfigFlags({.WINDOW_RESIZABLE, .VSYNC_HINT})
	rl.InitWindow(SettingsConfig.window.width, SettingsConfig.window.height, NAME)
	defer rl.CloseWindow()

	rl.SetTargetFPS(60)
	rl.SetTraceLogLevel(.ALL)

	target := rl.LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT)
	rl.SetTextureFilter(target.texture, .POINT)

	fmt.printfln("%b", SettingsConfig.window.fullscreen)

	Assets = make_assets()

	switch (current_scene) {
	case .MENU:
		load_menu()
	case .GAME:
		load_game()
	}

	if !DEBUG {
		rl.SetExitKey(.KEY_NULL)
	}

	for (running) {
		dt := rl.GetFrameTime()
		scale := min(f32(rl.GetScreenWidth()) / f32(GAME_WIDTH), f32(rl.GetScreenHeight()) / f32(GAME_HEIGHT))
		rl.SetMouseOffset(
			i32(-(f32(rl.GetScreenWidth()) - (f32(GAME_WIDTH) * scale)) * 0.5),
			i32(-(f32(rl.GetScreenHeight()) - (f32(GAME_HEIGHT) * scale)) * 0.5),
		)
		rl.SetMouseScale(1 / scale, 1 / scale)

		if rl.WindowShouldClose() {
			running = false
		}

		if (rl.IsKeyPressed(.F11) || (rl.IsKeyDown(.LEFT_ALT) && rl.IsKeyPressed(.ENTER))) {
			toggle_fullscreen()
		}

		switch (current_scene) {
		case .MENU:
			update_menu(dt)
		case .GAME:
			update_game(dt)
		}

		rl.BeginTextureMode(target)
		rl.ClearBackground(rl.Color{15, 15, 15, 255})
		switch (current_scene) {
		case .MENU:
			draw_menu()
		case .GAME:
			draw_game()
		}

		switch current_scene {
		case .MENU:
			draw_ui_menu()
		case .GAME:
			draw_ui_game()
		}
		rl.EndTextureMode()

		// Draw scaled texture
		rl.BeginDrawing()
		rl.ClearBackground(rl.BLACK)
		rl.DrawTexturePro(
			target.texture,
			{0, 0, f32(target.texture.width), -(f32(target.texture.height))},
			{
				(f32(rl.GetScreenWidth()) - (f32(GAME_WIDTH) * scale)) * 0.5,
				(f32(rl.GetScreenHeight()) - (f32(GAME_HEIGHT) * scale)) * 0.5,
				f32(GAME_WIDTH) * scale,
				f32(GAME_HEIGHT) * scale,
			},
			{0, 0},
			0.0,
			rl.WHITE,
		)
		rl.EndDrawing()
	}

	switch (current_scene) {
	case .MENU:
		unload_menu()
	case .GAME:
		unload_game()
	}
}
