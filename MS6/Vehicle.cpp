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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype>
#include <cstring>
#include "Vehicle.h"
#include <sstream>
#include <fstream>
#include <vector>


using namespace std;
namespace sdds {
	Vehicle::Vehicle() {
		m_makeAndModel = nullptr;
		setEmpty();
	}

	Vehicle::Vehicle(const char* plate, const char* makeMode) {
		if (plate != nullptr && plate[0] == '\0' && strlen(plate) <= MAX_CHAR
			&& makeMode != nullptr && makeMode[0] != '\0' && strlen(makeMode) > MIN_MODEL) {
			strncpy(m_licensePlate, plate, MAX_CHAR);
			m_licensePlate[MAX_CHAR] = '\0';
			m_makeAndModel = new char[strlen(makeMode) + 1];
			strcpy(m_makeAndModel, makeMode);
			m_parkSpotNo = 0;
		}
		else {
			m_makeAndModel = nullptr;
			m_licensePlate[0] = '\0';
			m_parkSpotNo = 0;
		}
	}

	Vehicle::~Vehicle() {
		if (m_makeAndModel != nullptr) {
			delete[] m_makeAndModel;
			m_makeAndModel = nullptr;
		}
	}

	void Vehicle::setEmpty() {
		m_parkSpotNo = 0;
		m_licensePlate[0] = '\0';
		if (m_makeAndModel != nullptr) {
			delete[] m_makeAndModel;
			m_makeAndModel = nullptr;
		}
	}

	bool Vehicle::isEmpty() const {
		return m_licensePlate[0] == '\0';
	}

	const char* Vehicle::getLicensePlate() const {
		return m_licensePlate;
	}

	const char* Vehicle::getMakeModel() const {
		return m_makeAndModel;
	}

	bool Vehicle::setMakeModel(const char* makeMode) {
		int len = 0;
		if (makeMode != nullptr && makeMode[0] != '\0') {
			len = strlen(makeMode);
			if (len >= MIN_MODEL && len <= MAX_MODEL) {
				delete[] m_makeAndModel;
				m_makeAndModel = nullptr;
				m_makeAndModel = new char[strlen(makeMode) + 1];
				strcpy(m_makeAndModel, makeMode);
				return true;
			}
		}
		else
			setEmpty();
		return false;
	}



	int Vehicle::getParkingSpot()const {
		return m_parkSpotNo;
	}

	bool Vehicle::setParkingSpot(int spotNo) {
		if (spotNo >= 0) {
			m_parkSpotNo = spotNo;
			return true;
		}
		else
			setEmpty();
		return false;
	}

	bool Vehicle::operator==(const char* plate)const {
		char* check1 = nullptr;
		char* check2 = nullptr;

		if (m_licensePlate[0] != '\0') {

			check1 = new char[9];
			strcpy(check1, m_licensePlate);
		}
		else {
			return false;
		}
		if (plate != nullptr && plate[0] != '\0') {

			check2 = new char[9];
			strcpy(check2, plate);
		}
		else {
			delete[] check1;
			check1 = nullptr;

			return false;
		}
		if (strcmp(check1, check2) == 0) {

			delete[] check1;
			delete[] check2;

			check1 = nullptr;
			check2 = nullptr;

			return true;
		}
		else {
			delete[] check1;
			delete[] check2;

			check1 = nullptr;
			check2 = nullptr;

			return false;
		}
	}

	bool Vehicle::operator==(const Vehicle& v1) const {
		return *this == v1.m_licensePlate;
	}

	std::istream& Vehicle::read(std::istream& is) {
		
		char t_makeAndModel[MAX_MODEL + 1];
		bool escap = false;
		bool check = true;
		setEmpty();
		if (isCsv()) {
			is >> m_parkSpotNo;
			if (is.fail()) {
				check = false;
			}
			is.ignore(8,',');
			is.getline(m_licensePlate, MAX_CHAR + 1, ',');
			
			is.getline(t_makeAndModel, MAX_MODEL + 1, ',');
			if (strlen(t_makeAndModel) < 2) {
				check = false;
			}
			int len = strlen(m_licensePlate);
			for (int i = 0; i < len; i++) {
				m_licensePlate[i] = toupper(m_licensePlate[i]);
			}
			
		}
		else {
			cout << "Enter Licence Plate Number: ";
			bool escp = false;		
			is.getline(m_licensePlate, 10, '\n');

			while (!escp) {
				m_licensePlate[0] = '\0';				
				is.getline(m_licensePlate, 10, '\n');				
				if (is.fail()||strlen(m_licensePlate) > MAX_CHAR || strlen(m_licensePlate) < 2) {
					is.clear();
					escp = false;

					cout << "Invalid Licence Plate, try again: ";
					is.clear();
				}
					else {
						escp = true;
						for (unsigned int i = 0; i < strlen(m_licensePlate); i++) {
							m_licensePlate[i] = toupper(m_licensePlate[i]);
						}
					}
				}			

			cout << "Enter Make and Model: ";						
			
			do {				
				escap = true;
				t_makeAndModel[0] = '\0';
				is.clear();
				is.getline(t_makeAndModel, 61, '\n');
				
				if (is.fail()||strlen(t_makeAndModel) > MAX_MODEL || strlen(t_makeAndModel) < MIN_MODEL) {
					escap = false;
				}
				
				else {
					escap = strlen(t_makeAndModel) <= MAX_MODEL && strlen(t_makeAndModel) >= MIN_MODEL;
				}

			} while (!escap&& cout << "Invalid Make and model, try again: ");
		}
		if (check) {
			m_makeAndModel = new char[strlen(t_makeAndModel) + 1];
			strcpy(m_makeAndModel, t_makeAndModel);
		   }
				else {
					setEmpty();
					}			
				is.clear();
				return is;
			}

	ostream& Vehicle::write(ostream& os)const {
		if (isCsv()) {
			os << m_parkSpotNo << "," << m_licensePlate << "," << m_makeAndModel << ",";
		}
		else
			if (isEmpty()) {
				os << "Invalid Vehicle Object\n";
			}
			else {
				os << "Parking Spot Number: ";
				if (m_parkSpotNo) {
					os << m_parkSpotNo << endl;
					os << "Licence Plate: " << m_licensePlate << endl;
					os << "Make and Model: " << m_makeAndModel << endl;
				}
				else {
					os << "N/A\n";
					os << "Licence Plate: " << m_licensePlate << endl;
					os << "Make and Model: " << m_makeAndModel << endl;
				}
			}
		return os;
	}
}