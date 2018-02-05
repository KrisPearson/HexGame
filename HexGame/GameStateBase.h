#pragma once
#include "SDL.h"

class HexgameCore;

namespace State {
	class GameStateBase {

	public:
		GameStateBase(HexgameCore& application/*, ConsolePrinter& printer*/) : gameRef(&application) {};
		~GameStateBase();

		// SDL Methods
		virtual void Input() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw() = 0;

		// Console Methods
		virtual void UpdateConsole() =0;

	protected:
		HexgameCore* gameRef;
		//ConsolePrinter* m_p_printer;

		//OptionsMenu* m_p_optionsMenu;

	};
}

