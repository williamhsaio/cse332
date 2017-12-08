// Ifeoma Ufondu and Halley Cummings
// ID: 442034 & 437513
// gamePieces.h
// File Explanation: This is the header file that holds are the enums and prototypes for 
// the game pieces

#pragma once

#include "GamePieceHeader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include "GameBaseHeader.h"
using namespace std;

enum errors { successTTT, playerQuit, gameOver, Draw, nextTurn };

class Gomoku : public GameBase {

private:
	vector<GamePiece> board;
	char currentPlayer = 'B';  //To be moved to the gameBase
	int playerCounter = 0;
	unsigned int rows;
	unsigned int cols;
	bool isPlayerB;


public:
	Gomoku();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual void print();
	virtual void save();
	virtual bool coordinateValid(unsigned int row, unsigned int col);

	friend ostream& operator<<(ostream& os, const Gomoku& gmk); //Making it so that when you call TicTacToe
																// the computer knows what to display

};
