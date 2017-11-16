#pragma once
using namespace std;
#include <string>
#include "GameBaseHeader.h"

class TicTacToeGame : public GameBase {
	friend ostream &operator<<(ostream &out, const TicTacToeGame &game);

public:
	TicTacToeGame();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual void print();
private:
	bool currentPlayerIsX;
	string XHistory;
	string OHistory;
	unsigned int currentPathsToWin;
};

// declaration for ostream operator
ostream &operator<<(ostream &out, const TicTacToeGame &game);