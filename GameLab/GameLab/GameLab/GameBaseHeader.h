#pragma once
//TicTacToeHeader.h
//Halley Cummings
//Includes declarations for TicTacToeGame class member variables and functions, as well as an overloaded declaration for the ostream operator.

#include "GamePieceHeader.h"
#include <vector>
#include <iostream>
#include <string>

class GameBase {
public:
	GameBase();
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool draw() = 0;
	int prompt(unsigned int &a, unsigned int &b);
	virtual int turn() = 0;
	int play();
	virtual bool coordinateValid(unsigned int row, unsigned int col)=0;


protected:
	//member variables common to all games
	unsigned int rows; //set size of tic tac toe board to be 5 x 5
	unsigned int cols;
	vector<GamePiece> board; // creates empty vector
	unsigned int displayLength;
	unsigned int turns;
};



