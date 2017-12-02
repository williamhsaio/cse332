// OverloadingStudio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Header.h"
using namespace std;

Overloader::Overloader(int i = 0) 
 : i(i){}

 ostream &operator<< ( ostream &out, const Overloader &O) {
	out << O.i;
	return out;
}

 bool Overloader::operator< (const Overloader & rhs) {
	 return (i < rhs.i);
 }

 Overloader& Overloader::operator= (const Overloader & rhs) {
	 i = rhs.i;
	 return *this;
 }

 bool operator== (const Overloader &lhs, const Overloader &rhs) {
	 return (lhs.i == rhs.i);
 }

int main()
{
	Overloader one = Overloader(1);
	Overloader two = Overloader(2);
	Overloader zero = Overloader();

	cout << one << two << zero << endl; // 120

	cout << (one < two) << endl; // true
	one = zero;
	cout << one << zero << endl; // 00

	cout << (one == zero) << endl; // true
    return 0;
}

