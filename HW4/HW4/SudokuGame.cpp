#include "stdafx.h"
#include "GameBaseHeader.h"
#include "SudokuHeader.h"
#include "Lab4Header.h"
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

bool SudokuGame::loadSavedFile() {
	ifstream SudokuInFile("SudokuGame.txt");
	string line;
	if (SudokuInFile.is_open()) {
		// read in saved game state
		int row = 8;
		unsigned int col = 0;
		int value;
		while (getline(SudokuInFile, line)) {
			if (line == "No Save") {
				// file is empty of saved game
				cout << "No previous game was saved. Using initial set up." << endl;
				return false;
			}
			col = 0;
			istringstream iss(line);
			while (iss >> value) {
				if (col > cols) {
					// too many values in this row
					cout << "Invalid saved file. Used initial game set up." << endl;
					return false;
				}
				if (value != 0) {
					if (value < 0) {
						board[9 * row + col].displayChar = to_string(-1 * value); // negative values in saved file denote permanent values
						permanentVal.push_back(9 * row + col);
					}
					else {
						board[9 * row + col].displayChar = to_string(value);
					}
				}
				++col;
			}
			--row;
		}
		if (row != -1) { // this means that more or less than 9 rows were found in the saved file.
			cout << "Invalid number of rows read from input file. Using initial game set up." << endl;
			return false;
		}
	}
	return true;
}
SudokuGame::SudokuGame() {
	rows = 9;
	cols = 9;
	// initialize board to be full of empty GamePieces
	for (unsigned int i = 0; i < rows*cols; ++i) {
		board.push_back(GamePiece());
	}
	bool usedSavedFile = loadSavedFile(); // try to find a saved version and use it
   if(!usedSavedFile) {
		// no saved game found; use base file
	   cout << "Loading clean gameboard." << endl;
		ifstream SudokuInFile("sudoku0.txt");
		if (SudokuInFile.is_open()) {
			// read in initial game state
			int row = 8; //unsigned because goes negative when end of rows is reached and I need to check that.
			unsigned int col = 0;
			unsigned int value;
			string line;
			while (getline(SudokuInFile, line)) {
				col = 0;
				istringstream iss(line);
				while (iss >> value) {
					if (value != 0) {
						board[9 * row + col].displayChar = to_string(value);
						permanentVal.push_back(9 * row + col);
					}
					else {
						board[9 * row + col].displayChar = " "; // convert all 0 spaces to blank values in vector
					}
					++col;
				}
				--row;
			}
			if (row != -1) {
				throw fileReadError; // didn't finish reading lines
			}
		}
		else {
			throw fileReadError;
		}
	}
	
}

bool SudokuGame::done() {
	// index 9*row + col
	int squaresIndices[] = { 10, 13, 16, 37,40,43,64,67,70 };
	bool wasFound[] = { false, false, false, false, false, false, false, false, false };
	int squarePeers[] = { -10,-9,-8,-1,0,1,8,9,10 }; // relationship of each index to its peers
	int character;
	int i;
	for (int square = 0; square < 9; ++square) {
		// check that all the squares on the board have all the numbers
		i = squaresIndices[square];
		for (int s = 0; s < 9; ++s) {
			character = (char)board[i + squarePeers[s]].displayChar.at(0) - '0';
			if ((character < 10) && (character > 0)) {
				wasFound[character - 1] = true;
			}
			else {
				return false;
			}
		}
		for (int j = 0; j < 9; ++j) {
			if (!wasFound[j]) {
				// some value wasn't found in this 3x3 square
				return false;
			}
			else {
				wasFound[j] = false; // reset for next round
			}
		}
	}
	// now check all rows have all values
	for (int row = 0; row < 9; ++row) {
		for (int col = 0; col < 9; ++col) {
			character = (char)board[rows*row + col].displayChar.at(0) - '0';
			if ((character < 10) && (character > 0)) {
				wasFound[character - 1] = true;
			}
			else {
				return false;
			}
		}
		for (int j = 0; j < 9; ++j) {
			if (!wasFound[j]) {
				// some value wasn't found in this row
				return false;
			}
			else {
				wasFound[j] = false; // reset for next round
			}
		}
	}

	// now check all cols have all values
	for (int col = 0; col < 9; ++col) {
		for (int row = 0; row < 9; ++row) {
			character = (char)board[rows*row + col].displayChar.at(0) - '0';
			if ((character < 10) && (character > 0)) {
				wasFound[character - 1] = true;
			}
			else {
				return false;
			}
		}
		for (int j = 0; j < 9; ++j) {
			if (!wasFound[j]) {
				// some value wasn't found in this row
				return false;
			}
			else {
				wasFound[j] = false; // reset for next round
			}
		}
	}
	// made it this far -> the game is complete
	return true;
}



bool SudokuGame::draw() {
	return false;
}

bool SudokuGame::isPermanent(unsigned int index) {
	for (unsigned int i = 0; i < permanentVal.size(); ++i) {
		if (index == permanentVal[i]) {
			return true;
		}
	}
	return false;
}

bool SudokuGame::coordinateValid(unsigned int row, unsigned int col) {
	//check coordinate is valid for the Sudoku board
	if ((row < 0) || (row > rows - 1)) {
		// coordinate value is invalid
		cout << "Please enter a row coordinate between 0 and " << (rows - 1) << endl;
		// call turn again to get a valid coordinate
		return false;
	}
	if ((col < 0) || (col > cols - 1)) {
		// coordinate value is invalid
		cout << "Please enter a column coordinate between 0 and " << (cols - 1) << endl;
		// call turn again to get a valid coordinate
		return false;
	}
	if (isPermanent(cols*row + col)) {
		cout << "This is a permanent value provided at the start of the game. Please enter a different coordinate." << endl;
		return false;
	}
	return true;
}

int SudokuGame::promptValue(int &val) {
	string display;
	cin >> display;
	makeLowercase(display);
	if (display == string("quit")) {
		return quitGame;
	}
	if (display.size() > 1) {
		cout << "Please enter a valid number 1 - 9." << endl;
		return promptValue(val);
	}
	istringstream iss(display);
	iss >> val;

	if ((val < 10) && (val > 0)) {
		return success;
	}
	else {
		cout << "The value entered was not between 1 and 9; please try again." << endl;
		return promptValue(val);
	}
}

int SudokuGame::turn() {
	//call prompt function

	unsigned int row; unsigned int col;
	int promptResult = prompt(row, col);

	//check if game was ended
	if (promptResult == quitGame) {
		return quitGame;
	}
	//checking validity of move is done in prompt method
	// make move 
	int index = rows*row + col;
	// read in value to display
	cout << "Please enter value 1-9 to insert at this space." << endl;
	int display;
	int result = promptValue(display);
	if (result == quitGame) {
		return quitGame;
	}

	board[index].displayChar = to_string(display);

	//print board for current move
	print();

	return success;
}


// declaration for ostream operator <<
ostream &operator<<(ostream &out, const SudokuGame &game) {
	vector<GamePiece> pieces = game.board;
	for (int r = (int)game.rows - 1; r >= -1; --r) {
		if ((r == -1) || (r == 2) || (r == 5)) {
			out << "==||===|===|===||===|===|===||===|===|===||" << endl;
		}
		else {
			out << "--||---|---|---||---|---|---||---|---|---||" << endl;
		}
		for (int c = -1; c < (int)game.cols; ++c) {

			// if in the -1 row or column, print markers
			if ((r == -1) && (c == -1)) {
				out << "# ";
			}
			else if (r == -1) {
				out << c << " ";
			}
			else if (c == -1) {
				out << r << " ";
			}
			else {
				// print each character plus needed white space
				string display = pieces[game.cols*r + c].displayChar;
				out << display << " ";
			}
			if ((c == -1) || (c == 2) || (c == 5) || (c == 8)) {
				out << "|| ";
			}
			else {
				out << "| ";
			}
		}
		out << endl; // print a new line at the end of every row
	}
	return out;
}

void SudokuGame::print() {
	cout << *this << endl;
}

void SudokuGame::save() {
	string response;
	while ((response != "Yes") && (response != "No")) {
		cout << "Would you like to save this game? Yes or No" << endl;
		cin >> response;
	}

	if (response == "Yes") {
		ofstream SudokuFile;
		SudokuFile.open("SudokuGame.txt");
		int row = 8;
		unsigned int col = 0;
		while (row != -1) {
			col = 0;
			while (col != cols) {
				string value = board[cols*row + col].displayChar;
				if (value == " ") {
					SudokuFile << "0 ";
				}
				else if(isPermanent(cols*row + col)) {
					SudokuFile << "-" << value << " "; // negative denotes it is permanent
				}
				else {
					SudokuFile << value << " ";
				}
				++col;
			}
			if (row >= 0) { // go to next row of file
				SudokuFile << endl;
			}
			--row;
		}
		SudokuFile.close();
	}
	else {
		// do not want to save game
		ofstream GomokuFile;
		GomokuFile.open("SudokuGame.txt");
		GomokuFile << "No Save";
		GomokuFile.close();
	}
}