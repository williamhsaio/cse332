
#pragma once
//Lab2Header.h
//Halley Cummings : halley@wustl.edu
//Declarations of array indices and possible failures. To be used by Lab2.cpp.

#include "GamePieceHeader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

enum arrayIndices { programName, gameName, numArguments };
enum failures {
	success, quitGame, drawnGame, gameInterrupted, numCmdArgumentsIncorrect, gameNameInvalid
};

//function declarations
int usageMessage(const string & programNameRef, const string & directions);
//int makeLowercase(string & text);