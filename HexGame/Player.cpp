#include "Player.h"
#include "HexGameCore.h"
#include "Graph.h"

#include "InputComponent.h"

#include <iostream>

Player::~Player() {
	//if (input != nullptr)
		//delete input;
}




void Player::Update() {
	input->Update(*this);
}

void Player::PlaceNode(int x, int y) {
	std::cout << "PLACE NODE" << std::endl;
	HexgameCore::GetInstance().GetGraph()->SetNodeOwner(x, y, playerColour);
}

bool Player::GetIsHuman() const {
	 return input->GetIsHuman(); 
}

void Player::AllowInput(bool allowInput) const {
	input->SetAllowInput(allowInput);
}

void Player::RequestInput() {
	input->Update(*this);
}
