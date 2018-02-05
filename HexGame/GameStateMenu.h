#pragma once
#include "GameStateBase.h"
namespace State {
	class GameStateMenu :
		public GameStateBase {
	public:
		GameStateMenu(HexgameCore& application);
		~GameStateMenu();

		void Input() override;

		void Update(float dt) override;

		void Draw() override;


		void UpdateConsole() override;

	};
}

