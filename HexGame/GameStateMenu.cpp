#include "GameStateMenu.h"
#include "HexGameCore.h"
#include "Player.h"
#include "GameStateHexPlay.h"

#include <iostream>

using namespace std;


State::GameStateMenu::GameStateMenu(HexgameCore & application) 
	: GameStateBase(application) {
}

State::GameStateMenu::~GameStateMenu() {

}

void State::GameStateMenu::Input() {
	// Handle Input (input could be handled via Update in player object?)
}

void State::GameStateMenu::Update(float dt) {
	// Update Logic
}

void State::GameStateMenu::Draw() {
	// Render Graphics
}

void State::GameStateMenu::UpdateConsole() {
	cout << "Welcome to HEX" << endl;
	cout << "==============" << endl << endl;

	cout << "Attempt to create a path from one side of the board to the other." << endl;
	cout << "Red wins if a path is created from Top to Bottom, and Blue wins if a path is created from Left to Right" << endl << endl;

	cout << "Please choose your game mode." << endl;
	cout << "[1] Human V Human" << endl;
	cout << "[2] Human V Computer" << endl;

	bool isValid;
	char input = ' ';

		//printf("\nWould you like to be X or O: (O goes first!!)");
		do {
			isValid = true;
			if (!(std::cin >> input)) {
				std::cout << "Invalid input!";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				isValid = false;
			}
			else if (input == '1') {
				string name;

				cout << "Enter a name for Player 1 (Red)" << endl;
				cout << "Name: ";
				cin >> name;
				gameRef->CreatePlayer(name, true);

				cout << "Enter a name for Player 2 (Blue)" << endl;
				cout << "Name: ";
				cin >> name;
				gameRef->CreatePlayer(name, true);
			}
			else if (input == '2') {
				string name;

				cout << "Enter a name for Player 1 (Red)" << endl;
				cout << "Name: ";
				cin >> name;
				gameRef->CreatePlayer(name, true);

				gameRef->CreatePlayer("CPU", false);
			}
			else {
				std::cout << "Please Choose an option!";
				isValid = false;
			}
		} while (isValid == false);

		HexgameCore::GetInstance().ChangeState(std::make_unique<State::GameStateHexPlay>(HexgameCore::GetInstance()));
}
