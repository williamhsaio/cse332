// Lab2Source.cpp : Defines the entry point for the console application.
// Halley Cummings : halley@wustl.edu
// Program takes in a game name and starts that game, taking user input to play.


#include "stdafx.h"
#include "Lab4Header.h"
#include "GamePieceHeader.h"
#include "TicTacToeHeader.h"
#include "GomokuHeader.h"
#include "GameBaseHeader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

int makeLowercase(string & text) {
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		if (text[i] < (int)'[' && text[i] > 64)
		{
			text[i] = text[i] + 32; // perform transformation for ASCII characters 
		}
	}
	return success;
}


int usageMessage( const string & directions)
{
	cout << "Please run the game by " << directions << endl;
	return success;
}

int main(int argc, char* argv[])
{	
	shared_ptr<GameBase> newGame;
	try {
		newGame = shared_ptr<GameBase> (GameBase::inputArgs(argc, argv));
	}
	catch (bad_alloc b) {
		return memoryError;
	}
	if (newGame == nullptr) {
		// some error with input
		usageMessage("passing 'TicTacToe' or 'Gomoku' as a command line argument. ");
		return commandLineArgsInvalid;
	}
	else {
		return newGame->play();
	}

}