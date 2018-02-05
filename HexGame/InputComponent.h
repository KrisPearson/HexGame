#pragma once

// Class modelled off of the Component Pattern.
// Intended to be used by the Player class and its derivitives to handle input from Player objects.

class Player;

class InputComponent {
public:
	virtual ~InputComponent() {};

	virtual void Update(Player& player) = 0;

	inline bool GetIsHuman() { return isHuman;  }

	inline void SetAllowInput(bool allowInput) { this->allowInput = allowInput;  }

protected:
	bool isHuman;

	bool allowInput;
};

