/* ------------------------------------------------------
Final Project Milestone 4
Module: ReadWritable
Filename: ms4_VehicleTester.cpp
Version 0.9
Author	Xiaozhuan Li(OOP244 NAA)
Revision History
-----------------------------------------------------------
Date      Reason
2020/3/25  Preliminary release
2020/3/27
-----------------------------------------------------------*/
#ifndef SDDS_VEHICLE_H__
#define SDDS_VEHICLE_H__
#include <iostream>
#include "ReadWritable.h"
using namespace std;
namespace sdds {
	const int MIN_CHAR = 1;
	const int MAX_CHAR = 8;
	const int MIN_MODEL = 2;
	const int MAX_MODEL = 60;
	class Vehicle : public ReadWritable {
		char m_licensePlate[MAX_CHAR + 1];
		char* m_makeAndModel;
		int m_parkSpotNo;
	protected:
		void setEmpty();
		bool isEmpty()const;
		const char* getLicensePlate() const;
		const char* getMakeModel() const;
		bool setMakeModel(const char*);
	public:
		Vehicle();
		Vehicle(const char*, const char*);
		~Vehicle();
		Vehicle(const Vehicle&) = delete;
		Vehicle& operator=(const Vehicle&) = delete;
		int getParkingSpot()const;
		bool setParkingSpot(int);
		bool operator==(const char*)const;
		bool operator==(const Vehicle& v1)const;
		istream& read(istream&);
		ostream& write(ostream&)const;
	};
}
#endif 
