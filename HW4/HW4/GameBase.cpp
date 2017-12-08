//TIcTacToeGame.cpp
//Halley Cummings
// Contains function definitions for GameBase class. Includes a default constructur definition.

#include "stdafx.h"
#include "GameBaseHeader.h"
#include "Lab4Header.h"
#include "TicTacToeHeader.h"
#include "GomokuHeader.h"
#include "SudokuHeader.h"
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

using namespace std;

shared_ptr<GameBase> GameBase::game = nullptr;


shared_ptr<GameBase> GameBase::instance() {
	if (GameBase::game == nullptr) {
		cout << "The current game is null." << endl;
		throw "The Game is Null";
	}
	return GameBase::game;
}



GameBase::GameBase()
	:rows(0), cols(0), displayLength(0) {
	//game = nullptr;
}

void GameBase::inputArgs(int argc, char* argv[]) {
	GameBase* newGame = 0;
	if (GameBase::game != nullptr) {
		throw "The Game isn't Null";
	}

	if (strcmp(argv[gameName], "TicTacToe") == 0) {
		try {
			TicTacToeGame *newGame = new TicTacToeGame();
			GameBase::game = make_shared<TicTacToeGame>(*newGame); //used to free up memory once all instances of game are nullptr
		}
		catch (bad_alloc b) {
			throw b;
		}
	}
	else if (strcmp(argv[gameName], "Gomoku") == 0) {
		try {
			Gomoku *newGame = new Gomoku();
			GameBase::game = make_shared<Gomoku>(*newGame);
		}
		catch (bad_alloc b) {
			throw b;
		}
	}
	else if (strcmp(argv[gameName], "Sudoku") == 0) {
		try {
			SudokuGame *newGame = new SudokuGame();
			GameBase::game = make_shared<SudokuGame>(*newGame);
		}
		catch (bad_alloc b) {
			throw b;
		}
		catch (int e) {
			throw e;
		}
	}
	else {
		GameBase *newGame = nullptr;

	}
}

int GameBase::prompt(unsigned int &row, unsigned int &col) {
	cout << "Please enter the coordinates of a square on the board in the format 'col,row' or enter 'quit' to end the game." << endl;
	string input;
	getline(cin, input); // take input in the form of a C++ string
	cout << endl; // print blank line

				  // remove any spaces from input line
	while (input.find(" ") != string::npos) {
		input.erase(input.find(" "), 1);
	}
	//make all characters lowercase
	makeLowercase(input);
	// check if this is the quit command
	if (input == "quit") {
		//ask them to save
		save();
		return quitGame;
	}

	if (input.size() > 5) {
		// improperly formatted string; call prompt again
		cout << "Input string is too long." << endl;
		return prompt(row, col);
	}

	if (input.size() == 0)
	{
		return prompt(row, col);
	}

	size_t commaChar = input.find(",");
	if (commaChar != std::string::npos) {
		// if comma is found in string, replace with space
		input.replace(commaChar, 1, " ");
		if (input.find(",") != std::string::npos) {
			// more than one comma was found
			cout << "Insert only one comma between coordinates." << endl;
			return prompt(row, col);
		}
	}
	else {
		// comma is not between coordinates; call prompt again
		cout << "Insert comma between coordinates." << endl;
		return prompt(row, col);
	}

	if (input.size() < 3) {
		// not enough coordinates entered
		cout << "Please enter two coordinate values." << endl;
		return prompt(row, col);
	}
	unsigned int colVal;
	unsigned int rowVal;
	stringstream iss(input);
	iss >> colVal >> rowVal;

	// at this point, 2 coordinates have been found. Range of coordinates has not been checked -- 
	// each game has different requirements. Call coordinateValid() to check.

	if (!coordinateValid(rowVal, colVal)) {
		// coordinate is invalid for this gameboard
		return prompt(row, col);
	}

	// coordinate is valid - > play a turn
	row = rowVal;
	col = colVal;

	return success;
}

int GameBase::play() {
	// print initial gameboard
	cout << "GAMEBOARD" << endl;
	print(); // print out current gameboard
	cout << endl;

	while (!draw() && !done()) {
		//call turn repeatedly while valid moves are left and no one has won
		int turnResult = turn();
		if (turnResult == quitGame) { // check if a user quit 
			cout << "Game ended after " << turns << " turns. " << endl;
			return quitGame;
		}
		++turns;
	}

	if (done()) {
		cout << "The current player won after " << turns << " turns." << endl;
		return success;
	}
	else if (draw()) {
		cout << endl;
		cout << "A draw occured after " << turns << " turns -- no valid moves remain." << endl;
		return drawnGame;
	}
	return gameInterrupted; // ended in unexpected way (not win, draw, or quit)
}

