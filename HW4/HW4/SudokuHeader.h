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
	virtual void save();
	virtual bool coordinateValid(unsigned int row, unsigned int col);
	vector<unsigned int> permanentVal;
private:
	int promptValue(int &val);
	bool isPermanent(unsigned int index);
	bool loadSavedFile();
};

// declaration for ostream operator
ostream &operator<<(ostream &out, const SudokuGame &game);
