#pragma once
//TicTacToeHeader.h
//Halley Cummings
//Includes declarations for TicTacToeGame class member variables and functions, as well as an overloaded declaration for the ostream operator.

#include "GamePieceHeader.h"
#include <vector>
#include <iostream>
#include <string>

class GameBase {
	friend ostream &operator<<(ostream &out, const GameBase &gameClass);
public:
	GameBase();

protected:
	//member variables common to all games
	unsigned int rows; //set size of tic tac toe board to be 5 x 5
	unsigned int cols;
	vector<GamePiece> board; // creates empty vector
};

// declaration for ostream operator
ostream &operator<<(ostream &out, const GameBase &gameClass);