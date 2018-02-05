#pragma once
#include "InputComponent.h"

class Player;

class HumanInputComponent :
	public InputComponent {
public:
	HumanInputComponent() { isHuman = true; };
	~HumanInputComponent();

	void Update(Player& player) override;

protected:


	/*TODO: Inform GameState of event, which will proceed to perform appropriate event.
			Could bind each event using callback/ delegate?		
	*/
	void OnKeyPressed();

	void OnKeyReleased();

	void OnMouseMoved();

	void OnMousePressed();

	void OnMouseReleased();

	int mouseX, mouseY;
	int pmouseX, pmouseY;
	int mouseButton;
	int keyDown, keyUp;
	bool ctrlPressed, shiftPressed, altPressed;
};

