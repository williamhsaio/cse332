#include "stdafx.h"
#include "Lab3Header.h"
#include "TicTacToeHeader.h"
#include "Gomoku.h"
#include <iostream>
#include <string>

using namespace std;



int main(int argc, char* argv[]) {
	if (argc != 2) {
		//usage(argv[0]);
		cout << "command line" << endl;
		return numCmdArgumentsIncorrect;   ///Checks how many arguments have been passed, only 2 should be passed
	}
	else if (strcmp(argv[1], "Gomoku") != 0) {
		//usage(argv[0]);
		cout << argv[1] << endl;
		cout << "wrong game" << endl;
		return gameNameInvalid;
	}

	Gomoku gmk;
	cout << gmk << endl;
	gmk.play();


	return 0;
}


////void usage(char* a) {
////	cout << a << "To run this program please input " << a << " TicTacToe" << endl;
////}