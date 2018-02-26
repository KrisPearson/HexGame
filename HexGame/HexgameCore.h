#pragma once
#include <vector>
#include <stack>
#include <memory>

#include "Graph.h"
#include "GameStateBase.h"
#include "SDL.h"

class HexgameCore {
private:

	HexgameCore();

	// Stop the compiler generating methods of copy the object
	HexgameCore(HexgameCore const& copy);            
	HexgameCore& operator=(HexgameCore const& copy); 

public:

	static HexgameCore& GetInstance() {
		static HexgameCore instance;
		return instance;
	}

	~HexgameCore();


	// Runs initial setup, including window and graphics initialisation
	void SetupGame();

	// Triggers the game loop
	void StartGame();

	class Player*  GetCurrentPlayer();

	// Check to see whethe rplayer input is valid
	bool CheckCoordInputValid(int xLoc, int yLoc);

	// Spawns a Player instance
	void CreatePlayer(std::string name, bool isHuman);


	inline Graph<HexNode>* GetGraph() const { return hexGraph; };

	// both Pop and Push state
	void ChangeState(std::unique_ptr<State::GameStateBase> state) const;


	// Changes the current player to the next
	void NextPlayer() const;

	// Looks for a path for the current player. If a path is found - returns True
	bool CheckForPath() const;

private:

	// Handles input and output based on the current game state TODO: Implement state-machine
	void GameLoop();

	bool TimerUpdate();

	void PushState(std::unique_ptr<State::GameStateBase> state);
	void PopState();

	// Stores the last node modified by a player
	Node* lastPlacedNode = nullptr;

	// TEMP: used to handle the game over state
	bool isRunning;

	// Used to track the current player
	mutable int currentPlayerIndex = 0;

	Graph<HexNode>* hexGraph;

	// Stores a list of players and is used to store player information and handle turns.
	std::vector<class Player> players;

	SDL_Surface* screen;
	SDL_Surface* bg;

	std::stack<std::unique_ptr<State::GameStateBase>> m_states;

	double frameCount;
	double startTime;
	double lastTime;

};

