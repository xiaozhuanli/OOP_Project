/* ------------------------------------------------------
Final Project Milestone 5
Module: Car and Motorcycle
Filename: ms5_CarMotorcycleTester.cpp
Version 0.9
Author	Xiaozhuan Li(244NAA)
Revision History
-----------------------------------------------------------
Date      Reason
2020/3/27  Preliminary release
-----------------------------------------------------------
comment out car or motorcycle include and functions to test
individually.

*/
#ifndef SDDS_CAR_H__
#define SDDS_CAR_H__
#include <iostream>
#include "Vehicle.h"
using namespace std;
namespace sdds {
	class Car : public Vehicle {
		char m_licensePlate[MAX_CHAR + 1]{};
		char* m_makeAndModel{};
		int m_parkSpotNo{};
		bool m_carWash = 0;
	public:
		Car();
		Car(const char*, const char*, int, bool);
		~Car();
		Car(const Vehicle&) = delete;
		Car& operator=(const Car&) = delete;
		istream& read(istream&);
		ostream& write(ostream&)const;
		//ifstream& read(std::ifstream& is);
	};
}
#endif 
