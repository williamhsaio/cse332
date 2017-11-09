// Lab2Source.cpp : Defines the entry point for the console application.
// Halley Cummings : halley@wustl.edu
// Program takes in a game name and starts that game, taking user input to play.


#include "stdafx.h"
#include "Lab2Header.h"
#include "GamePieceHeader.h"
#include "TicTacToeHeader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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


int usageMessage(const string & programNameRef, const string & directions)
{
	cout << "Please run the " << programNameRef << "game by " << directions << endl;
	return success;
}

int main(int argc, char* argv[])
{	
	if (argc != numArguments) {
		usageMessage("TicTacToe", "passing 'TicTacToe' as a command line argument. ");
		return numCmdArgumentsIncorrect;
	}
	if (strcmp(argv[gameName], "TicTacToe")) {
		usageMessage("TicTacToe", "passing 'TicTacToe' as a command line argument. ");
		return gameNameInvalid;
	}
	TicTacToeGame game = TicTacToeGame(); //declare a new empty gameboard
	return game.play(); //gives status of game played : success, drawn, quit
}