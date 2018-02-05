// C++ for C Programmers, Part B
// Homework 4 - Implement Hex Board
//
// Description: This program emulates the board game "Hex" in which two players compete to link opposing edges of a borad of hexagonal tiles.
// Author: Kristian Pearson
// Date: 21/01/2018

#include <iostream>
#include <SDL.h>

#include "HexgameCore.h"
#include "GameConstants.h"

using namespace std;



int main(int argc, char * args[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	else 
		cout << "SDL initialization succeeded!" << endl;

	//HexgameCore* game = new HexgameCore();
	//game.SetupGame();
	//game.StartGame();

	HexgameCore::GetInstance().SetupGame();
	HexgameCore::GetInstance().StartGame();
	return 0;
}