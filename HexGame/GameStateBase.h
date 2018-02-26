// The GammeState is used to encapsulate behaviour for each state of play.
// New states should be derived from the GameStateBAse class and its abstact virtual methods overriden.
// The Gamestate is used by calling it's Update, Input and Draw methods inside the game loop.

#pragma once
#include "SDL.h"

class HexgameCore;

namespace State {
	class GameStateBase {

	public:
		GameStateBase(HexgameCore& application) : gameRef(&application) {};
		~GameStateBase() {} ;

		// SDL Methods
		virtual void Input() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw() = 0;

		// Console Methods
		virtual void UpdateConsole() =0;

	protected:
		HexgameCore* gameRef;

	};
}

