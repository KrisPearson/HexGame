#include "GameStateHexPlay.h"
#include "HexGameCore.h"
#include "Player.h"

#include <iostream>

using namespace std;


State::GameStateHexPlay::GameStateHexPlay(HexgameCore & application) 
	: GameStateBase(application) {

}

State::GameStateHexPlay::~GameStateHexPlay() {
}



void State::GameStateHexPlay::Input() {
	//listen for input ...

}

void State::GameStateHexPlay::Update(float dt) {
	// Update Logic
}

void State::GameStateHexPlay::Draw() {
	// Render Graphics
}

void State::GameStateHexPlay::UpdateConsole() {
	Player* currentPlayer = HexgameCore::GetInstance().GetCurrentPlayer();
	currentPlayer->AllowInput(true);
	if (currentPlayer != nullptr) {
		if (currentPlayer->GetIsHuman()) {
			cout << currentPlayer->GetName() << " - it's your turn. Please Enter Hex Node Coordinates: " << endl;

			std::string str_choice, str_x, str_y;

			cin >> str_choice;

			unsigned int x, y;
			size_t pos = std::string::npos;
			pos = str_choice.find_first_of(",");
			if (pos == std::string::npos)
			{
				cout << str_choice << " is an illegal entry. Please enter a legal coordinate." << endl;
				//legal_move = false;
				return;
			}

			str_x = str_choice.substr(0, pos);
			str_y = str_choice.substr(pos + 1);
			x = stoul(str_x, nullptr, 0);
			y = stoul(str_y, nullptr, 0);
			//HexAddResult res = hb->AddHex(HexValue::First, x, y);
			if (gameRef->CheckCoordInputValid(x, y)) {
				cout << "Valid Move" << endl << endl;
			}
			else {
				cout << "Invald Move" << endl;
				return;
			}
		}
		else {			
			cout << currentPlayer->GetName() << " is thinking...." << endl;
			currentPlayer->RequestInput();
		}
	}

	currentPlayer->AllowInput(false);


	//CheckHexAddResult(x, y, board_size, res);

	if (HexgameCore::GetInstance().CheckForPath()) {
		cout << "GAME OVER!" << endl;
		//gameOver = true;
		// TODO: Switch Game State
	}


	HexgameCore::GetInstance().GetGraph()->PrintGraph();

	HexgameCore::GetInstance().NextPlayer();

	/*
	cin >> rowNum;
	if (cin.fail()) {
	cout << "Error: Please enter a valid number" << endl << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return;
	}
	//else {
	cout << endl << "y: ";
	cin >> colNum;
	if (cin.fail()) {
	cout << "Error: Please enter a valid number" << endl << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return;
	}
	*/

	//gameRef->hexGraph->PrintGraph();
}
