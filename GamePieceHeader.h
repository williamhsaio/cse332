#pragma once
//GamePieceHeader.h
//Halley Cummings
//Enum, struct, declarations for GamePiece.cpp.

#pragma once
#include <string>
using namespace std;

enum pieceColor { white, black, red, invalidColor, noColor };

struct GamePiece {
	GamePiece();
	pieceColor color;
	string name;
	string displayChar;
};