/* ------------------------------------------------------
Final Project Milestone 3
Module: ReadWritable
Filename: ms3_RWTester.cpp
Version 1.0
Author	Xiaozhuan Li(OOP244 NAA)
Revision History
-----------------------------------------------------------
Date      Reason
2020/3/23  Preliminary release
2020/3/23
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ReadWritable.h"
using namespace std;
namespace sdds {
	ReadWritable::ReadWritable() {
		commaSeparatedValues = false;
	}

	ReadWritable::~ReadWritable() {
	}

	bool ReadWritable::isCsv() const {
		return commaSeparatedValues;
	}

	void ReadWritable::setCsv(bool value) {		
		 commaSeparatedValues = value;		
	}

	std::ostream& operator<<(std::ostream& os, const ReadWritable& rw) {
		rw.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is, ReadWritable& rw) {
		rw.read(is);
		return is;
	}
}