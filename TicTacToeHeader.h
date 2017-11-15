#pragma once
using namespace std;
#include <string>
#include "GameBaseHeader.h"

class TicTacToeGame : public GameBase {
public:
	TicTacToeGame();
	bool done();
	bool draw();
	int prompt(unsigned int &a, unsigned int &b);
	int turn();
	int play();
	
private:
	bool currentPlayerIsX;
	string XHistory;
	string OHistory;
	unsigned int currentPathsToWin;
};

//void makeLowercase(string & text);