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
:rows(0), cols(0), displayLength(0){}

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
		return quitGame;
	}
	if (input.size() > 3) {
		// improperly formatted string; call prompt again
		cout << "Input string is too long." << endl;
		return prompt(row, col);
	}
	size_t commaChar = input.find(",");
	if (commaChar != 1) {
		// comma is not between coordinates; call prompt again
		cout << "Insert comma between coordinates." << endl;
		return prompt(row, col);
	}

	if (input.size() < 3) {
		// not enough coordinates entered
		cout << "Please enter two coordinate values." << endl;
		return prompt(row, col);
	}
	//input.replace(commaChar, 1, " "); // replaces , char with space char in input string
	unsigned int colVal = input.at(0) - '0'; // performs char to int conversion
	unsigned int rowVal = input.at(2) - '0';
	if ((rowVal <= 0) || (rowVal >= rows - 1)) {
		// coordinate value is invalid
		cout << "Please enter a row coordinate between 1 and " << (rows - 2) << endl;
		return prompt(row, col);
	}
	if ((colVal <= 0) || (colVal >= cols - 1)) {
		// coordinate value is invalid
		cout << "Please enter a column coordinate between 1 and " << (cols - 2) << endl;
		return prompt(row, col);
	}

	if (board[rows*rowVal + colVal].displayChar != " ") {
		// this space is already occupied
		cout << "This space is already full." << endl;
		return prompt(row, col);
	}

	// input is an acceptable coordinate
	row = rowVal;
	col = colVal;

	return success;
}