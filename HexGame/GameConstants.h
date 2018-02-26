#pragma once

const int MAX_NODE_COUNT = 1001;

const bool IS_CONSOLE_MODE = true;

const double GAME_SPEED = 33.33;

const int BOARD_SIZE = 5;

enum class NodeOwner {
	None = 0,
	Red = 1,
	Blue = 2
};

// The value displayed in the console to represent the NodeOwner
static const char* nodeSymbols[] = {
	"O",
	"R",
	"B"
};

enum class GameState {
	INIT_SPLASH = 0,
	PLAY = 1,
	END_SPLASH = 2
};