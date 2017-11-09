#pragma once
//TicTacToeHeader.h
//Halley Cummings
//Includes declarations for TicTacToeGame class member variables and functions, as well as an overloaded declaration for the ostream operator.

#include "GamePieceHeader.h"
#include <vector>
#include <iostream>
#include <string>

class TicTacToeGame {
	friend ostream &operator<<(ostream &out, const TicTacToeGame &gameClass);
public:
	
	TicTacToeGame();
	bool done();
	bool draw();
	int prompt(unsigned int &a, unsigned int &b);
	int turn();
	int play();
private:
	unsigned int rows; //set size of tic tac toe board to be 5 x 5
	unsigned int cols;
	bool currentPlayerIsX;
	string XHistory;
	string OHistory;
	unsigned int currentPathsToWin;
	vector<GamePiece> board; // creates empty vector
};

// declaration for ostream operator
ostream &operator<<(ostream &out, const TicTacToeGame &gameClass);

