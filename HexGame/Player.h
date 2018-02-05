#pragma once
#include <string>
#include "GameConstants.h"

class InputComponent;

// The player class is used to record and store player information. It is intened to eventually be used to also handle input from bot Human and AI players 
class Player {
public:
	Player(std::string name, int index, NodeOwner colour, InputComponent* input) : playerName(name), playerIndex(index), playerColour(colour), input(input)  {};
	~Player();

	// Returns the name of this player
	inline std::string GetName() const { return playerName;  }

	// Returns the index of this player.
	inline int GetIndex() const { return playerIndex;  }

	// Used to compare one player with another
	inline friend bool operator==(const Player& playera, const Player& playerb) {
		return (playera.GetIndex() == playerb.GetIndex());
	};

	// Returns the team colour of this player
	NodeOwner GetColour() { return playerColour; }

	void Update();
	
	void PlaceNode(int x, int y);

	bool GetIsHuman() const;

	void AllowInput(bool allowInput)const;

	void RequestInput();

private :

	// Dictates whether the player is Human controlled or AI controlled
	bool isHuman = true;

	/*
	The values in these variables are updated every iteration of the game loop
	and should be used in the onKey??? and onMouse??? methods to change the game
	variables and state.
	*/
	int mouseX, mouseY;
	int pmouseX, pmouseY;
	int mouseButton;
	int keyDown, keyUp;
	bool ctrlPressed, shiftPressed, altPressed;

	bool gameover;


	//TODO: Decide where to stor ethis information (player? Here?) and create appropriate accessor functions

	/*
	struct ControlInputs {
	int mouseX, mouseY;
	int pmouseX, pmouseY;
	int mouseButton;
	int keyDown, keyUp;
	bool ctrlPressed, shiftPressed, altPressed;
	}
	*/

	// returnConrolInput const*;



private:
	//Stores the name of this player. Primarily used for feedback and display purposes
	const std::string playerName;

	// Stores the index of this player. Primarily used to in turn handling
	const int playerIndex;

	// Stores the team colour of this player. Primarily used to handle Node ownership and win conditions.
	const NodeOwner playerColour;

private:
	InputComponent* input;
};

