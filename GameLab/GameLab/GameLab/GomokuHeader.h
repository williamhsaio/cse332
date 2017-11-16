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

//defines a point
//struct points {
//	unsigned int a;
//	unsigned int b;
//};

class Gomoku : public GameBase{

private:
	vector<GamePiece> board;
	//vector<char>rows;
	char currentPlayer = 'B';  //To be moved to the gameBase
	int playerCounter = 0;
	unsigned int rows;
	unsigned int cols;
	bool isPlayerB;


public:
	//Make sure that I change certain functions to Virtual
	Gomoku();
	virtual bool done();
	virtual bool draw();
	//virtual int prompt(unsigned int&a, unsigned int&b); // defined in base class for both games
	virtual int turn();
	//virtual int play();
	virtual void print();


	friend ostream& operator<<(ostream& os, const Gomoku& gmk); //Making it so that when you call TicTacToe
																// the computer knows what to display

};
