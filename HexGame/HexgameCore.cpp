#include "HexgameCore.h"
#include "SDL.h"
#include "Graph.h"
#include "Node.h"
#include "Player.h"
#include "Pathfinder.h"

#include "GameStateMenu.h"
#include "GameStateHexPlay.h"

#include "HumanInputComponent.h"
#include "ComputerInputComponent.h"

#define NOMINMAX
#include "windows.h" // TODO: Adapt to platform


#include <iostream>

using namespace std;


HexgameCore::HexgameCore() {

}


HexgameCore::~HexgameCore() {
	delete hexGraph;
}


void HexgameCore::SetupGame() {
	//TODO: Perform Initial SDL tasks here...
}


void HexgameCore::StartGame() {

	hexGraph = new Graph<HexNode>(BOARD_SIZE);
	hexGraph->PrintGraph();

	PushState(std::make_unique<State::GameStateMenu>(*this)); 

	isRunning = true;

	GameLoop();
}

void HexgameCore::GameLoop() {

	startTime = timeGetTime(); // This uses windows.h TODO: Adapt to permit different platforms
	frameCount = 0;
	lastTime = 0;

	while (isRunning) {

		if (!IS_CONSOLE_MODE) {
			m_states.top()->Draw();
			m_states.top()->Input();
		}
		else {
			m_states.top()->UpdateConsole();
		}



		//SDL_Delay(10);
		//GetUserInput();
		//Update();
		//SDL_BlitSurface(bg, NULL, screen, NULL);
		//Draw();
		//SDL_Flip(screen);
		//LateUpdate();

		//int rowNum;
		//int colNum;

		//players[currentPlayerIndex].GetInput();
		/*

		cout << players[currentPlayerIndex].GetName() << " - Please Enter Hex Node Coordinates." << endl;
		cout << "x: ";
		cin >> rowNum;
		if (cin.fail()) {
			cout << "Error: Please enter a valid number" << endl << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		//else {
		cout << endl << "y: ";
		cin >> colNum;
		if (cin.fail()) {
			cout << "Error: Please enter a valid number" << endl << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		if (CheckCoordInputValid(rowNum, colNum)) {

			if (CheckForPath()) {
				cout << "GAME OVER!" << endl;
				gameOver = true;
				// TODO: Switch Game State
			}
			hexGraph->PrintGraph();

			NextPlayer();

		}
		else {
			cout << "Invalid Move. Please try again." << endl;
			continue;
		}
		*/
	}
}

#pragma region == Game State Functions == 
void HexgameCore::PushState(unique_ptr<State::GameStateBase> state) {
	m_states.push(move(state));
}

void HexgameCore::PopState() {
	m_states.pop();
}

void HexgameCore::ChangeState(std::unique_ptr<State::GameStateBase> state) const {
	HexgameCore::GetInstance().PopState();
	HexgameCore::GetInstance().PushState(move(state));
}

#pragma endregion

Player* HexgameCore::GetCurrentPlayer() {
	//assert(players[currentPlayerIndex] != nullptr);
	return &players[currentPlayerIndex];
}

// Uses the last placed tile to find a path between the edges of the board.
// If a path is found, then True will be returned
bool HexgameCore::CheckForPath() const {
	Pathfinder pathFinder;
	return (pathFinder.SearchForPath(lastPlacedNode, hexGraph->GetMaxX(), hexGraph->GetMaxY()));
}

void HexgameCore::CreatePlayer(string name, bool isHuman) {
	int index = players.size();
	NodeOwner colour = static_cast<NodeOwner>(index + 1);
	if (isHuman) {
		players.push_back(Player(name, index, colour, new HumanInputComponent())); // TODO: Adapt to allow CompuerInputComponent
	}
	else {
		players.push_back(Player(name, index, colour, new ComputerInputComponent() ));
	}
}

/*
// Checks to see whether the input is an integer and whether the
bool HexgameCore::CheckCoordInputValid(int xLoc, int yLoc) {

	if (hexGraph->FindNode(xLoc, yLoc, lastPlacedNode)) {
		//if (nodeRef != nullptr) {
			if (lastPlacedNode->ModifyOwner(players[currentPlayerIndex].GetColour())) {
				cout << "VALID" << endl;
				return true;
			}
		//}
	}
	else return false;
}
*/

// Checks to see whether the move is valid, whilst also assigning 
bool HexgameCore::CheckCoordInputValid(int xLoc, int yLoc) {
	Node* tempNode;

		// Check to see whether the Node exists and, if so, store it in the temp Node variable
	if (hexGraph->FindNode(xLoc, yLoc, tempNode)) { 
			// Check if the Node has an owner
		if (tempNode->GetOwner() == NodeOwner::None) {
		//if (lastPlacedNode->GetOwner() != players[currentPlayerIndex].GetColour()) {

			lastPlacedNode = tempNode;
			return lastPlacedNode->ModifyOwner(players[currentPlayerIndex].GetColour());
		}
		else {
			cout << "Failed to ModifyOwner of Node at " << lastPlacedNode->GetCoordinates().X() << ", " << lastPlacedNode->GetCoordinates().Y() << endl;;
			return false;
		}
	}
	else return false;
}


void HexgameCore::NextPlayer() const {
	if (players[currentPlayerIndex] == players.back()) currentPlayerIndex = 0; // return to the first player
	else currentPlayerIndex++; // or go to the next player
}

bool HexgameCore::TimerUpdate() {
	double currentTime = timeGetTime() - lastTime;

	if (currentTime < GAME_SPEED) return false;

	frameCount++;
	lastTime = timeGetTime();

	return true;

}
