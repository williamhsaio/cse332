#pragma once
// Ifeoma Ufondu
// ID: 442034
// TTTPiece.cpp
// File Explanation: This is the source file that defines the game pieces
#include "stdafx.h" //-2, I had to add this to both your source files, and your program wasn't compiling. AH
#include "GamePieceHeader.h"
#include "Lab4NewHeader.h"
#include "GameBaseHeader.h"
#include "GomokuHeader.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

Gomoku::Gomoku()
	:isPlayerB(true), rows(19), cols(19), board() {
	rows = 19;
	cols = 19;

	ifstream GomokuInFile("Gomoku.txt");
	string line;
	if (GomokuInFile.is_open()) {
		getline(GomokuInFile, line);
	}
	if (line != "No Save") {
		string moves;
		string whoTurn;
		//intialize based on contents of txt
		getline(GomokuInFile, moves);
		getline(GomokuInFile, whoTurn);
		string m;
		stringstream loadedMoves(moves);
		for (int i = 0; i < rows*cols; i++) {
			loadedMoves >> m;
			if (m == "-") {
				m = " ";
			}
			cout << m << endl;
			GamePiece temp = GamePiece();
			temp.displayChar = m;
			board.push_back(temp);

		}
	}

	else {
		// initialize board to be full of empty GamePieces
		for (unsigned int i = 0; i < rows*cols; ++i) {
			board.push_back(GamePiece());
		}
	}
	/*
	for (int i = 0; i < board.size(); i++) {
		cout << board[i].name << endl;
	}*/

}


ostream &operator<<(ostream &out, const Gomoku &gameclass) {
	vector<GamePiece> pieces = gameclass.board;
	int vertRow = 19;
	for (int i = 0; i < (int)gameclass.cols; i++) { // changed to cols instead of row
		out << setw(2) << vertRow << " ";
		for (int j = 0; j < (int)gameclass.rows; j++) {
			//out << gameclass.board[360 - (19 * i) - (18 - j)].displayChar << "  ";
			out << gameclass.board[(gameclass.rows*gameclass.cols - 1) - (gameclass.cols * i) - (gameclass.rows - j - 1)].displayChar << "  ";
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
	for (int i = 0; i < (rows - 1); i++) {
		//the different diagonals
		int wDR = 0;
		int bDR = 0;
		int wDL = 0;
		int bDL = 0;
		int count = 0;
		int position = i;
		while ((position) < (rows*cols)) { //checks you're inbounds
			if ((board[position].displayChar == "B")) {
				bDR++;
				wDR = 0;
				if (bDR == 5) {
					//cout << "Player B won the game after diagonally1  " << turns << " turns." << endl;
					return true;
				}
			}
			if ((board[position].displayChar == "W")) {
				wDR++;
				bDR = 0;
				if (wDR == 5) {
					//cout << "Player W won the game after diagonally " << turns << " turns." << endl;
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
		while ((position) < (rows*cols)) { //checks you're inbounds
			if ((board[position].displayChar == "B")) {
				bDL++;
				wDL = 0;
				if (bDL == 5) {
					//cout << "Player B won the game afte diagonallyr " << turns << " turns." << endl;
					return true;
				}
			}
			if ((board[position].displayChar == "W")) {
				wDL++;
				bDL = 0;
				if (wDL == 5) {
					//cout << "Player W won the game after diagonally  " << turns << " turns." << endl;
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
	for (int i = 0; i < (cols - 1); i++) {  //the vertical side
		int whCounter = 0;
		int bhCounter = 0;
		int wvCounter = 0;
		int bvCounter = 0;
		for (int j = 0; j < (rows - 1); j++) {
			if (board[cols*i + j].displayChar == "B") {
				bhCounter++;
				whCounter = 0;
				if (bhCounter == 5) {
					//cout << "Player B won the game after horizontal" << turns << " turns." << endl;
					return true;
				}

			}
			if (board[cols*j + i].displayChar == "B") {
				bvCounter++;
				wvCounter = 0;
				if (bvCounter == 5) {
					//cout << "Player B won the game after horizontal " << turns << " turns." << endl;
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
					//cout << "Player W won the game after vertiacal " << turns << " turns." << endl;
					return true;
				}

			}
			if (board[cols*j + i].displayChar == "W") {
				wvCounter++;
				bvCounter = 0;
				if (wvCounter == 5) {
					//cout << "Player W won the game after vertical " << turns << " turns." << endl;
					return true;
				}

			}
		}

	}
	return false;
}

bool Gomoku::draw() {
	//for (int i = 1; i < 19; i++) {
	//	for (int j = 1; j < 19; j++) {
	//		if (board[cols*i + j].displayChar == " ") {
	//			return false;
	//		}
	//		if (done()) {
	//			return false;
	//		}
	//	}
	//}
	bool wDraw = false;
	bool bDraw = false;
	//make a copy of the current board
	//vector<GamePiece> wBoard = board;
	//vector<GamePiece> bBoard = board;
	vector<GamePiece> original = board;

	for (int k = 0; k < 2; k++) {
		char placeHolder = ' ';
		if (k == 0) {
			placeHolder = 'W';
		}
		else {
			placeHolder = 'B';
		}
		for (int i = 1; i < rows; i++) {
			for (int j = 1; j < cols; j++) {
				if (board[cols*i + j].displayChar == " ") {
					board[cols*i + j].displayChar = placeHolder;
				}
			}
		}
		if (done()) {
			board = original;
			return false;

		}
		board = original;
	}
	return true;
}


bool Gomoku::coordinateValid(unsigned int row, unsigned int col) {
	// check that this coordinate is valid for the Gomoku game
	if ((row < (rows + 1)) && (row > 0) && (col < (cols + 1)) && (col > 0)) { //if its within the playing area
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

	string currentPlayer = "W";
	if (isPlayerB) {
		currentPlayer = "B";
	}

	cout << "It is  " << currentPlayer << "'s turn." << endl;

	while (x != success) { //while prompt returns false meaning a bad input, or you've quit the game
		if (x == quitGame) {
			cout << "Player " << currentPlayer << " has quit the game." << endl;
			return quitGame; //Player has quit
		}
		x = prompt(a, b);
	}

	board[cols*(a - 1) + (b - 1)].displayChar = currentPlayer;  //puts the proper char in the space

	playerCounter++; //keeps track of the # of turns
					 // print board
	print();

	isPlayerB = !isPlayerB; // switch players

	return success;
}

void Gomoku::print() {
	cout << *this << endl;
}

void Gomoku::save() {
	string response;
	while ((response != "Yes") && (response != "No")) {
		cout << "Would you like to save this game? Yes or No" << endl;
		cin >> response;
	}

	if (response == "Yes") {
		ofstream GomokuFile;
		GomokuFile.open("Gomoku.txt");
		GomokuFile << "Gomoku" << endl;
		for (int i = 0; i < rows*cols; i++) {
			if (board[i].displayChar == " ") {
				board[i].displayChar = "-";
			}
			GomokuFile << board[i].displayChar << " ";
		}
		GomokuFile << endl;
		if (isPlayerB) {
			GomokuFile << "B Turn" << endl;
		}
		else {
			GomokuFile << "W Turn" << endl;
		}

	}
	else if (response == "No") {
		ofstream GomokuFile;
		GomokuFile.open("Gomoku.txt");
		GomokuFile << "No Save";
		GomokuFile.close();
	}

}