#pragma once
#include "GameStateBase.h"

namespace State {
	class GameStateHexPlay :
		public GameStateBase {
	public:
		GameStateHexPlay(HexgameCore& application);
		~GameStateHexPlay();

		void Input() override;

		void Update(float dt) override;

		void Draw() override;

		void UpdateConsole() override;
	};
}

