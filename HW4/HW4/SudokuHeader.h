#pragma once
using namespace std;
#include <string>
#include "GameBaseHeader.h"

class SudokuGame : public GameBase {
	friend ostream &operator<<(ostream &out, const SudokuGame &game);

public:
	SudokuGame();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual void print();
	virtual bool coordinateValid(unsigned int row, unsigned int col);
private:
	int promptValue(int &val);
};

// declaration for ostream operator
ostream &operator<<(ostream &out, const SudokuGame &game);