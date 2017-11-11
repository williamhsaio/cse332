#include "stdafx.h"
#include "GameBaseHeader.h"
#include "TicTacToeHeader.h"
#include "Lab3Header.h"
#include <string>
#include <vector>
using namespace std;

TicTacToeGame::TicTacToeGame() 
	: currentPlayerIsX(true), XHistory("Player X: "), OHistory("Player O: "), currentPathsToWin(8){

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
	currentPathsToWin = 8; // starts at 8 each time the different paths are checked
	if (sameDisplayChar(board, 6, 7, 8, currentPathsToWin)) {
		return true; // bottom row
	}
	else if (sameDisplayChar(board, 11, 12, 13, currentPathsToWin)) {
		return true; //middle row
	}
	else if (sameDisplayChar(board, 16, 17, 18, currentPathsToWin)) {
		return true; //top row
	}
	else if (sameDisplayChar(board, 16, 11, 6, currentPathsToWin)) {
		return true; //first col
	}
	else if (sameDisplayChar(board, 12, 17, 7, currentPathsToWin)) {
		return true; //middle col
	}
	else if (sameDisplayChar(board, 18, 13, 8, currentPathsToWin)) {
		return true; // last col
	}
	else if (sameDisplayChar(board, 6, 12, 18, currentPathsToWin)) {
		return true; //upper diagonal
	}
	else if (sameDisplayChar(board, 16, 12, 8, currentPathsToWin)) {
		return true; //lower diagonal
	}
	else {
		return false; //no one wins
	}
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

int TicTacToeGame::prompt(unsigned int &row, unsigned int &col) {
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

int TicTacToeGame::turn() {
	char currentPlayer = 'O';
	if (currentPlayerIsX) {
		currentPlayer = 'X';
	}
	cout << "-------------------------------------------" << endl; // print line to divide between turns
	cout << "The current player is " << currentPlayer << endl;

	//call prompt function
	unsigned int row; unsigned int col;
	int promptResult = prompt(row, col);

	//check if game was ended
	if (promptResult == quitGame) {
		cout << "Player " << currentPlayer << " has ended the game." << endl;
		return quitGame;
	}
	//checking validity of move is done in prompt method
	// make move 
	int index = rows*row + col;
	board[index].displayChar = currentPlayer;


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

int TicTacToeGame::play() {
	// print initial gameboard
	cout << "GAMEBOARD" << endl;
	cout << *this << endl;
	cout << endl;

	int turns = 0;
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
		if (currentPlayerIsX) {
			cout << endl;
			cout << "Player O won the game after " << turns << " turns." << endl;
		}
		else {
			cout << endl;
			cout << "Player X won the game after " << turns << " turns." << endl;
		}
		return success;
	}
	else if (draw()) {
		cout << endl;
		cout << "A draw occured after " << turns << " turns -- no valid moves remain." << endl;
		return drawnGame;
	}
	return gameInterrupted; // ended in unexpected way (not win, draw, or quit)
}