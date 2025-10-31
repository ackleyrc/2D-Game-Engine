#pragma once
#include <string>
#include "EngineConfig.h"
#include "Color.h"

struct EngineConfig;

struct GameConfig {
	EngineConfig engineConfig = {
		.width = SCREEN_WIDTH,
		.height = SCREEN_HEIGHT,
		.windowTitle = "Maze Eater Game",
		.backgroundColor = Color( 0.06f, 0.06f, 0.12f, 1.0f ),
		.resizable = true
	};

	static constexpr int TILE_WIDTH = 16;
	static constexpr int TILE_HEIGHT = 16;
	static constexpr int TILE_ROWS = 36;
	static constexpr int TILE_COLS = 28;

	static constexpr int SCREEN_WIDTH = TILE_WIDTH * TILE_COLS;
	static constexpr int SCREEN_HEIGHT = TILE_HEIGHT * TILE_ROWS;
};