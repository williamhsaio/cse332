#include "stdafx.h"
#include "GameBaseHeader.h"
#include "TicTacToeHeader.h"
#include "Lab3Header.h"
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

TicTacToeGame::TicTacToeGame() 
	: currentPlayerIsX(true), XHistory("Player X: "), OHistory("Player O: "), currentPathsToWin(8){
	rows = 5;
	cols = 5;
	// initialize board to be full of empty GamePieces
	for (unsigned int i = 0; i < rows*cols; ++i) {
		board.push_back(GamePiece());
	}
}

bool sameDisplayChar(vector<GamePiece> board, unsigned int x, unsigned int y, unsigned int z, unsigned int &pathsToWin) {
	//returns true if all the display characters at a, b, c are the same and not empty
	string a = board.at(x).displayChar;
	string b = board.at(y).displayChar;
	string c = board.at(z).displayChar;
	bool allSame = ((a == b) && (b == c) && (a != " "));
	if (!allSame) {
		// no one has won on this combination
		//check if it is possible to win on this combination
		// decrease paths to win if line looks like this: X 0 " ", O " " X, " " X O, etc
		// don't decrease paths to win if there is more than one blank space in the line, or if there is 1 blank space and the other two characters match
		if ((a == " ") && (b != c) && (b != " ") && (c != " ")) {
			--pathsToWin;
		}
		else if ((b == " ") && (a != c) && (a != " ") && (c != " ")) {
			--pathsToWin;
		}
		else if ((c == " ") && (b != a) && (b != " ") && (a != " ")) {
			--pathsToWin;
		}
		else if ((a != " ") && (b != " ") && (c != " ")) {
			--pathsToWin;
		}
	}
	return allSame;
}

bool TicTacToeGame::done() {
	// checks whether there are 3 X's or 3 0's somewhere on the board
	//8 different cases that can result in done returning true
	//index = (5*y) + x
	bool isDone = false;
	currentPathsToWin = 8; // starts at 8 each time the different paths are checked
	if (sameDisplayChar(board, 6, 7, 8, currentPathsToWin)) {
		isDone = true; // bottom row
	}
	else if (sameDisplayChar(board, 11, 12, 13, currentPathsToWin)) {
		isDone = true;
	}
	else if (sameDisplayChar(board, 16, 17, 18, currentPathsToWin)) {
		isDone = true;
	}
	else if (sameDisplayChar(board, 16, 11, 6, currentPathsToWin)) {
		isDone = true;
	}
	else if (sameDisplayChar(board, 12, 17, 7, currentPathsToWin)) {
		isDone = true;
	}
	else if (sameDisplayChar(board, 18, 13, 8, currentPathsToWin)) {
		isDone = true;
	}
	else if (sameDisplayChar(board, 6, 12, 18, currentPathsToWin)) {
		isDone = true;
	}
	else if (sameDisplayChar(board, 16, 12, 8, currentPathsToWin)) {
		isDone = true;
	}
	if (isDone && (turns !=0 )) {
		if (currentPlayerIsX) {
			cout << endl;
			cout << "Player O won the game after " << turns << " turns." << endl;
		}
		else {
			cout << endl;
			cout << "Player X won the game after " << turns << " turns." << endl;
		}
		turns = 0; // set to 0 so message only prints once
	}
	return isDone;
}



bool TicTacToeGame::draw() {
	if (done()) { // if game is done, no draw
		return false;
	}
	if (currentPathsToWin > 0) {
		return false; // it is still possible to win for this game
	}
	// otherwise, game is a draw 
	return true;
}
 bool TicTacToeGame::coordinateValid(unsigned int row, unsigned int col) {
	 cout << "row " << row << " col " << col << endl;
	//check coordinate is valid for the TicTacToe board
	if ((row <= 0) || (row >= rows - 1)) {
		// coordinate value is invalid
		cout << "Please enter a row coordinate between 1 and " << (rows - 2) << endl;
		// call turn again to get a valid coordinate
		return false;
	}
	if ((col <= 0) || (col >= cols - 1)) {
		// coordinate value is invalid
		cout << "Please enter a column coordinate between 1 and " << (cols - 2) << endl;
		// call turn again to get a valid coordinate
		return false;
	}
	if (board[rows*row + col].displayChar != " ") {
		// this space is already occupied
		cout << "This space is already full." << endl;
		// call turn again to get a valid coordinate
		return false;
	}
	return true;
}
int TicTacToeGame::turn() {
	//call prompt function
	unsigned int row; unsigned int col;
	int promptResult = prompt(row, col);

	string currentPlayer = "O";
	if (currentPlayerIsX) {
		currentPlayer = "X";
	}
	cout << "-------------------------------------------" << endl; // print line to divide between turns
	cout << "The current player is " << currentPlayer << endl;


	//check if game was ended
	if (promptResult == quitGame) {
		cout << "Player " << currentPlayer << " has ended the game." << endl;
		return quitGame;
	}
	//checking validity of move is done in prompt method
	// make move 
	int index = rows*row + col;
	board[index].displayChar = currentPlayer;
	// updates displayLength if new display string is of longer length than previous ones
	if (currentPlayer.length() > displayLength) {
		displayLength = currentPlayer.length();
	}


	//print board for current move
	cout << *this << endl;
	//print player's history
	if (currentPlayerIsX) {
		XHistory += " (" + to_string(row) + "," + to_string(col) + "), ";
		cout << endl;
		cout << XHistory << endl;
	}
	else {
		OHistory += " (" + to_string(col) + "," + to_string(row) + "), ";
		cout << endl;
		cout << OHistory << endl;
	}

	//at end of turn, switch current player
	currentPlayerIsX = !currentPlayerIsX;
	return success;
}


// declaration for ostream operator <<
ostream &operator<<(ostream &out, const TicTacToeGame &game) {
	vector<GamePiece> pieces = game.board;
	cout << "display length " << game.displayLength << endl;
	for (int r = (int)game.rows - 1; r >= -1; --r) {
		for (int c = -1; c < (int)game.cols; ++c) {

			// if in the -1 row or column, print markers
			if ((r == -1) && (c == -1)) {
				out << " ";
			}
			else if (r == -1) {
				out << setw(game.displayLength+1) << c;
			}
			else if (c == -1) {
				out << r;
			}
			else {
				// print each character plus needed white space
				string display = pieces[game.cols*r + c].displayChar;
				out << setw(game.displayLength + 1) << display;
			}
		}
		out << endl; // print a new line at the end of every row
	}
	return out;
}

void TicTacToeGame::print() {
	cout << *this << endl;
}