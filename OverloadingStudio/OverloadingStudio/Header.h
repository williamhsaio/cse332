#pragma once
#include <iostream>
using namespace std;

class Overloader {
	friend ostream & operator<< ( ostream &out, const Overloader &O);
	friend  bool operator== (const Overloader &lhs, const Overloader &rhs);
public:
	Overloader(int i);
	bool operator< (const Overloader & rhs);
	Overloader& operator= (const Overloader & rhs);
private:
	int i;
};

 ostream &operator<< ( ostream &out, const Overloader &O);

 bool operator== (const Overloader &lhs, const Overloader &rhs);