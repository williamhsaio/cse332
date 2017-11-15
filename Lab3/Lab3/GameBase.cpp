//TIcTacToeGame.cpp
//Halley Cummings
// Contains function definitions for GameBase class. Includes a default constructur definition.

#include "stdafx.h"
#include "GameBaseHeader.h"
#include "Lab3Header.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

GameBase::GameBase()
:rows(0), cols(0), displayLength(0){

}

// declaration for ostream operator <<
ostream &operator<<(ostream &out, const GameBase &gameClass) {
	vector<GamePiece> pieces = gameClass.board;
	for (int r = (int)gameClass.rows - 1; r >= -1; --r) {
		for (int c = -1; c < (int)gameClass.cols; ++c) {
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
				out << pieces[gameClass.cols*r + c].displayChar << " ";
			}
		}
		out << endl; // print a new line at the end of every row
	}
	return out;
}