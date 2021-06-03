/* Citation and Sources...
Final Project Milestone 2
Module: Parking
Filename: Parking.h
Version 1.0
Author	 Xiaozhuan Li(OOP244NAA 162683189)
Revision History
-----------------------------------------------------------
Date      Reason
2020/03/13  Preliminary release
2020/03/16
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#ifndef SDDS_PARKING_H__
#define SDDS_PARKING_H__
#include <iostream> 
#include "Menu.h"
#include "Vehicle.h"
using namespace std;
namespace sdds {
	const int MAX_NO_OF_SPOTS = 100;
	const int MIN_NO_OF_SPOTS = 10;
	
	class Parking {
		int m_noSpots{};
		Vehicle* parkingSpot[MAX_NO_OF_SPOTS]{};
		int m_noPaked{};
		char* m_dataFileName{};		
		Menu* mainMenu{};
		Menu* subMenu{};		
		bool isEmpty()const;
		void parkingStatus()const;
		void parkVehicleMenu();
		void returnVehicle();
		void listVehicle();
		bool closeParking();
		bool exitParking()const;
		bool loadDataFile();
		void saveDataFile()const;
		operator bool() const;
	public:
		Parking(const Parking&) = delete;
		Parking& operator=(const Parking&) = delete;
		int run();
		Parking();
		Parking(const char*);
		Parking(const char*, int);
		~Parking();
	};
}
#endif 