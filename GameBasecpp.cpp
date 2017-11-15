////TIcTacToeGame.cpp
////Halley Cummings
//// Contains function definitions for GameBase class. Includes a default constructur definition.
//
#include "stdafx.h"
#include "gamebaseheader.h"
#include "lab3header.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

GameBase::GameBase()
	: rows(5), cols(5) {
	// initialize board to be full of empty gamepieces
	for (unsigned int i = 0; i < rows*cols; ++i) {
		board.push_back(GamePiece());
	}
}

// declaration for ostream operator <<

ostream &operator<<(ostream &out, const GameBase &gameclass) {
	vector<GamePiece> pieces = gameclass.board;
	for (int r = (int)gameclass.rows - 1; r >= -1; --r) {
		for (int c = -1; c < (int)gameclass.cols; ++c) {
			// if in the -1 row or column, print markers
			if ((r == -1) && (c == -1)) {
				out << "  ";
			}
			else if (r == -1) {
				out << c << " ";
			}
			else if (c == -1) {
				out << r << " ";
			}
			else {
				// print each character
				out << pieces[gameclass.cols*r + c].displayChar << " ";
			}
		}
		out << endl; // print a new line at the end of every row
	}
	return out;
}