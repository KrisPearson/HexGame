
// Original reference: https://codereview.stackexchange.com/questions/55365/input-handling-system-using-the-command-pattern
#pragma once
#include "Player.h"

#include <SDL.h>
#include <array>
#include <vector>


const int MAX_ACTION_INDEX = 100;

enum class InputType {
	ACTION,
	STATE,
	RANGE
};

enum class Action {
	EXECUTE = true,
	STOP = false
};

enum class State {
	PRESSED = true,
	RELEASED = false
};

class Command {
public: 
	virtual ~Command() {}
	virtual void Execute(Player* player) = 0;
	virtual InputType GetInputType() = 0;
};

class InputHandler {
public:
	InputHandler();
	~InputHandler();

private:
	// Pointers to all commands
	Command *leftMouse;

	std::array<Command*, MAX_ACTION_INDEX> commands;

	// Gameplay context
	std::array<State, MAX_ACTION_INDEX> states;
	std::array<Action, MAX_ACTION_INDEX> actions;

	bool InputMapping();
	void Dispatcher(std::vector<Command*> &commandQueue);

	void KeyDown(SDL_Event &event);
	void KeyUp(SDL_Event &event);

	bool IsHeld(int keyIndex);
	bool WasPressed(int keyIndex);

public:
	bool GenerateCommands(std::vector<Command*> &commandQueue);
	void BindKeyToCommand(int keyIndex, Command *command);
};

#pragma region Command Declarations 

class PlaceNode : public Command {
	void Execute(Player* player) override { player->PlaceNode();  }
};


#pragma endregion

