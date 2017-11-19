#pragma once
// Ifeoma Ufondu
// ID: 442034
// TTTPiece.cpp
// File Explanation: This is the source file that defines the game pieces
#include "stdafx.h" //-2, I had to add this to both your source files, and your program wasn't compiling. AH
#include "GamePieceHeader.h"
#include "Lab3Header.h"
#include "GameBaseHeader.h"
#include "GomokuHeader.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

Gomoku::Gomoku()
	:isPlayerB(true), rows(19), cols(19), board() {
	for (unsigned int i = 0; i < rows*cols; ++i) {
		board.push_back(GamePiece());
	}
}


ostream &operator<<(ostream &out, const Gomoku &gameclass) {
	vector<GamePiece> pieces = gameclass.board;
	int vertRow = 19;
	for (int i = 0; i < (int)gameclass.cols; i++) { // changed to cols instead of row
		out << setw(2) << vertRow << " ";
		for (int j = 0; j < (int)gameclass.rows; j++) {
			//	out << gameclass.board[360 - (19 * i) - (18 - j)].displayChar << "  ";
			out << gameclass.board[gameclass.cols*j + i].displayChar << "  ";
		}
		vertRow--;
		out << endl;
	}

	out << "X  1  2  3  4  5  6  7  8  9  ";
	out << "10 11 12 13 14 15 16 17 18 19" << endl;

	return out;
}


bool Gomoku::done() { //checks if there is 5 in a row
						  //loop through to check for 5 vertically
						  //check for diagonals
	for (int i = 0; i < 18; i++) {
		//the different diagonals
		int wDR = 0;
		int bDR = 0;
		int wDL = 0;
		int bDL = 0;
		int count = 0;
		int position = i;
		while ((position) < 361) { //checks you're inbounds
			if ((board[position].displayChar == "B")) {
				bDR++;
				wDR = 0;
				if (bDR == 5) {
					return true;
				}
			}
			if ((board[position].displayChar == "W")) {
				wDR++;
				bDR = 0;
				if (wDR == 5) {
					return true;
				}
			}
			if ((board[position].displayChar == " ")) {
				bDR = 0;
				wDR = 0;
			}
			position = position + 20;
		}

		position = i * 19;
		while ((position) < 361) { //checks you're inbounds
			if ((board[position].displayChar == "B")) {
				bDL++;
				wDL = 0;
				if (bDL == 5) {
					return true;
				}
			}
			if ((board[position].displayChar == "W")) {
				wDL++;
				bDL = 0;
				if (wDL == 5) {
					return true;
				}
			}
			if ((board[position].displayChar == " ")) {
				bDL = 0;
				wDL = 0;
			}
			position = position + 20;
		}
	}

	//check the horizonal and Vertical
	for (int i = 0; i < 18; i++) {  //the vertical side
		int whCounter = 0;
		int bhCounter = 0;
		int wvCounter = 0;
		int bvCounter = 0;
		for (int j = 0; j < 18; j++) {
			if (board[cols*i + j].displayChar == "B") {
				bhCounter++;
				whCounter = 0;
				if (bhCounter == 5) {
					return true;
				}

			}
			if (board[cols*j + i].displayChar == "B") {
				bvCounter++;
				wvCounter = 0;
				if (bvCounter == 5) {
					return true;
				}

			}
			if (board[cols*i + j].displayChar == " ") {
				bhCounter = 0;
				whCounter = 0;
			}
			if (board[cols*j + i].displayChar == " ") {
				bvCounter = 0;
				wvCounter = 0;
			}
			if (board[cols*i + j].displayChar == "W") {
				whCounter++;
				bhCounter = 0;
				if (whCounter == 5) {
					return true;
				}

			}
			if (board[cols*j + i].displayChar == "W") {
				wvCounter++;
				bvCounter = 0;
				if (wvCounter == 5) {
					return true;
				}

			}
		}

	}
	return false;
}

bool Gomoku::draw() {
	for (int i = 1; i < 19; i++) {
		for (int j = 1; j < 19; j++) {
			if (board[cols*i + j].displayChar == " ") {
				return false;
			}
			if (done()) {
				return false;
			}
		}
	}
	return true;
}


bool Gomoku::coordinateValid(unsigned int row, unsigned int col) {
	// check that this coordinate is valid for the Gomoku game
	if ((row < 20) && (row > 0) && (col < 20) && (col > 0)) { //if its within the playing area
		if (board[cols*(row - 1) + (col - 1)].displayChar != " ") {
			//this location is already full; prompt for a new coordinate
			cout << "This board location is not available." << endl;
			return false;
		}
		else {
			return true;
		}
	}
	else {
		// prompt for new coordinate
		cout << "The coordinates entered are not within the 19 x 19 board." << endl;
		return false;
	}
}

int Gomoku::turn() {
	unsigned int a;
	unsigned int b;
	int x = prompt(a, b);

	char currentPlayer = 'W';
	if (isPlayerB) {
		currentPlayer = 'B';
	}

	cout << "It is  " << currentPlayer << "'s turn." << endl;
	
	while (x != success) { //while prompt returns false meaning a bad input, or you've quit the game
		if (x == quitGame) {
			cout << "There were " << playerCounter << " moves played. Someone quit the game" << endl;
			return quitGame; //Player has quit
		}
		x = prompt(a, b);
	}

	board[cols*(b - 1) + (a - 1)].displayChar = currentPlayer;  //puts the proper char in the space

	playerCounter++; //keeps track of the # of turns
	cout << *this << endl;  //Dereferences the pointer to the current instance of the TicTacToeGame
							// Puts it into the output stream that we just redefined

	if (done()) {
		cout << currentPlayer << " wins!" << endl;
		return successTTT;
	}

	if (draw()) {
		cout << "There were " << playerCounter << " moves played. There are no winning moves left." << endl;
		return Draw;
	}


	if (isPlayerB == false) {
		isPlayerB = true;
	}
	else {
		isPlayerB = false;
	}


	return nextTurn;
}/*
int Gomoku::play() {
	while (int temp = turn()) {
		if (temp == nextTurn) {
			continue;
		}
		else {
			return temp;
		}
	}
	return successTTT;
}
*/
void Gomoku::print() {
	cout << *this << endl;
}

