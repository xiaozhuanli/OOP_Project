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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "ReadWritable.h"
#include "Car.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	Car::Car() {
		m_carWash = false;
	}

	Car::Car(const char* plate, const char* makeMode, int = 0, bool = 0) {
		if (plate != nullptr && plate[0] == '\0' && strlen(plate) <= MAX_CHAR
			&& makeMode != nullptr && makeMode[0] != '\0' && strlen(makeMode) > MIN_MODEL) {
			m_carWash = true;
		}
		else {
			m_makeAndModel = nullptr;
			m_licensePlate[0] = '\0';
			m_parkSpotNo = 0;
			m_carWash = 0;
		}
	}

	Car::~Car() {
	}

	istream& Car::read(istream& is) {
		char option[8];
		bool check = false;
		if (isCsv()) {
			Vehicle::read(is);
			is >> m_carWash;
			is.ignore(1000, '\n');
			is.clear();
		}
		else {
			
			cout << "\nCar information entry" << endl;
			Vehicle::read(is);
			cout << "Carwash while parked? (Y)es/(N)o: ";
			do {
				is>>option;
				is.ignore(1000, '\n');
				is.clear();
				if (strlen(option)==1&&(option[0] == 'Y'|| option[0] == 'y' || option[0] == 'N' || option[0] == 'n')) {
					check = true;
				}
				else {
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
			} while (!check);

			if (option[0] == 'Y' || option[0] == 'y') {
				m_carWash = true;
				cout << endl;
			}
			else {
				m_carWash = false;
				cout << endl;
			}
			
		}
		return is;
	}

	ostream& Car::write(ostream& os) const {
		if (isEmpty()) {
			os << "Invalid Car Object" << endl;
		}
		else {
			if (isCsv()) {
				os << "C,";
			}
			else {
				os << "Vehicle type: Car\n";
			}

			Vehicle::write(os);
			if (isCsv()) {
				os << m_carWash << endl;
			}
			else {
				if (m_carWash == true) {
					os << "With Carwash\n";
				}
				else {
					os << "Without Carwash\n";
				}
			}
		}
		return os;
	}
}