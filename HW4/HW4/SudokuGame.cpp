#include "stdafx.h"
#include "GameBaseHeader.h"
#include "SudokuHeader.h"
#include "Lab4NewHeader.h"
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

SudokuGame::SudokuGame() {
	rows = 9;
	cols = 9;
	// initialize board to be full of empty GamePieces
	ifstream SudokuInFile("Sudoku.txt");
	string line;
	if (SudokuInFile.is_open()) {
		getline(SudokuInFile, line);
	}
	if (line != "No Save") {
		string moves;
		//intialize based on contents of txt
		getline(SudokuInFile, moves);
		string m;
		stringstream loadedMoves(moves);
		for (int i = 0; i < rows*cols; i++) {
			loadedMoves >> m;
			cout << m << endl;
			if (m == "-") {
				m = " ";
			}
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

bool SudokuGame::coordinateValid(unsigned int row, unsigned int col) {
	//check coordinate is valid for the Sudoku board
	if ((row < 0) || (row >= rows - 1)) {
		// coordinate value is invalid
		cout << "Please enter a row coordinate between 0 and " << (rows - 1) << endl;
		// call turn again to get a valid coordinate
		return false;
	}
	if ((col < 0) || (col >= cols - 1)) {
		// coordinate value is invalid
		cout << "Please enter a column coordinate between 0 and " << (cols - 1) << endl;
		// call turn again to get a valid coordinate
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
		SudokuFile.open("Sudoku.txt");
		SudokuFile << "Sudoku" << endl;
		for (int i = 0; i < rows*cols; i++) {
			if (board[i].displayChar == " ") {
				board[i].displayChar = "-";
			}
			SudokuFile << board[i].displayChar << " ";
		}
		SudokuFile << endl;

	}
	else if (response == "No") {
		ofstream SudokuFile;
		SudokuFile.open("Sudoku.txt");
		SudokuFile << "No Save";
		SudokuFile.close();
	}
}