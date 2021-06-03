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
#include "Motorcycle.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	Motorcycle::Motorcycle() {
	}

	Motorcycle::Motorcycle(const char* plate, const char* makeMode, int = 0, bool = 0) {
		if (plate != nullptr && plate[0] == '\0' && strlen(plate) <= MAX_CHAR
			&& makeMode != nullptr && makeMode[0] != '\0' && strlen(makeMode) > MIN_MODEL) {
			hasSideCar = true;
		}
		else {
			m_makeAndModel = nullptr;
			m_licensePlate[0] = '\0';
			m_parkSpotNo = 0;
			hasSideCar = false;
		}
	}

	Motorcycle::~Motorcycle() {
	}

	istream& Motorcycle::read(istream& is) {
		char option;
		char nl;
		if (isCsv()) {
			Vehicle::read(is);
			is >> hasSideCar;
			is.ignore(1000, '\n');
		}
		else {
			cout << "\nMotorcycle information entry" << endl;
			Vehicle::read(is);
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			do {
				option = cin.get();
				nl = cin.get();
				if ((option != 'Y' && option != 'y' && option != 'N' && option != 'n') || nl != '\n') {
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
				if (nl != '\n') {
					cin.ignore(1000, '\n');
				}
			} while ((option != 'Y' && option != 'y' && option != 'N' && option != 'n') || nl != '\n');
			if (option == 'Y' || option == 'y') {
				hasSideCar = true;
				cout << endl;
			}
			else {
				hasSideCar = false;
				cout << endl;
			}
		}
		return is;
	}

	ostream& Motorcycle::write(ostream& os) const {
		if (isEmpty()) {
			os << "Invalid Motorcycle Object" << endl;
		}
		else {
			if (isCsv()) {
				os << "M,";
			}
			else {
				os << "Vehicle type: Motorcycle\n";
			}

			Vehicle::write(os);
			if (isCsv()) {
				os << hasSideCar << endl;;
			}
			else {
				if (hasSideCar) {
					os << "With Sidecar\n";
				}
			}
		}
		return os;
	}
}