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
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>
#include "Parking.h"
#include "Car.h"
#include "Motorcycle.h"


using namespace std;
namespace sdds {

	Parking::Parking(){
		m_noSpots = 0;
		m_noPaked = 0;
		m_dataFileName = nullptr;		
		*parkingSpot = nullptr;		
		
	}

	Parking::Parking(const char* dataFileName) {
		mainMenu = nullptr;
		subMenu = nullptr;
		if (dataFileName != nullptr && dataFileName[0] != '\0') {
			m_dataFileName = new char[strlen(dataFileName) + 1];
			strcpy(m_dataFileName, dataFileName);

			if (loadDataFile()) {
				mainMenu = new Menu("Parking Menu, select an action:");
				mainMenu->add("Park Vehicle");
				mainMenu->add("Return Vehicle");
				mainMenu->add("List Parked Vehicles");
				mainMenu->add("Close Parking (End of day)");
				mainMenu->add("Exit Program");
				subMenu = new Menu("Select type of the vehicle:", 1);
				subMenu->add("Car");
				subMenu->add("Motorcycle");
				subMenu->add("Cancel");
			}
		}
		else {
			cout << "Error in data file" << endl;
			m_dataFileName = nullptr;
			m_noSpots = 0;
		}
	}

	Parking::Parking(const char* dataFileName, int noSpots) {
		mainMenu = nullptr;
		subMenu = nullptr;
		if (dataFileName != nullptr && dataFileName[0] != '\0'&&noSpots>=MIN_NO_OF_SPOTS&& noSpots<=MAX_NO_OF_SPOTS) {
			m_dataFileName = new char[strlen(dataFileName) + 1];
			strcpy(m_dataFileName, dataFileName);
			m_noSpots = noSpots;

			if (loadDataFile()) {
				mainMenu = new Menu("Parking Menu, select an action:");
				mainMenu->add("Park Vehicle");
				mainMenu->add("Return Vehicle");
				mainMenu->add("List Parked Vehicles");
				mainMenu->add("Close Parking (End of day)");
				mainMenu->add("Exit Program");
				subMenu = new Menu("Select type of the vehicle:", 1);
				subMenu->add("Car");
				subMenu->add("Motorcycle");
				subMenu->add("Cancel");
			}
		}
		else {
			cout << "Error in data file" << endl;
			m_dataFileName = nullptr;
			m_noSpots = 0;
		}
	}

	Parking::~Parking() {
		saveDataFile();
		delete[] m_dataFileName;
		m_dataFileName = nullptr;
		delete mainMenu;
		mainMenu = nullptr;
		delete subMenu;
		subMenu = nullptr;
		for (int i = 0; i < m_noSpots; i++) {
			delete parkingSpot[i];
			parkingSpot[i] = nullptr;
		}
		
	}

	bool Parking::isEmpty()const {
		return m_dataFileName==nullptr;
	}

	void  Parking::parkingStatus()const {
		int availaSpots = m_noSpots - m_noPaked;
		cout << "****** Seneca Valet Parking ******" << endl;
		cout << "*****  Available spots: ";
		cout << setw(4) << left << availaSpots << " *****\n";
	}

	void  Parking::parkVehicleMenu(){
		Vehicle* vehicle=nullptr;
		
		bool found = false;
		if (m_noSpots == m_noPaked ) {
			cout << "Parking is full\n";
			return;
		}
		else {
			int option = 0;
			subMenu->display();

			if (!isEmpty()) {
				cin >> option;
				if (option == 3) {
					cout << "Parking cancelled\n";
					return;
				}
				else {
					if (option == 1) {
						vehicle = new Car;
						vehicle->setCsv(false);
						vehicle->read(std::cin);						
							
							for (int i = 0; i < m_noSpots && !found; i++) {
								if (parkingSpot[i] == nullptr) {
									parkingSpot[i] = vehicle;
									vehicle = nullptr;
									m_noPaked++;
									parkingSpot[i]->setParkingSpot(i + 1);
									found = true;
									cout << "Parking Ticket\n";
									parkingSpot[i]->write(std::cout);
									cout << endl;
								
							}
						
							
						}
							delete vehicle;
							vehicle = nullptr;
					}
					else if (option == 2) {
						vehicle = new Motorcycle;
						
					
						vehicle->setCsv(false);
						vehicle->read(std::cin);
						for (int i = 0; i < m_noSpots&& !found; i++) {
							if (parkingSpot[i] == nullptr) {

								parkingSpot[i] = vehicle;
								vehicle = nullptr;
								m_noPaked++;

								parkingSpot[i]->setParkingSpot(i + 1);
								found = true;
								cout << "Parking Ticket\n";
								parkingSpot[i] ->write(std::cout);								
								cout<<endl;
							}
						}						
					
						delete vehicle;
						vehicle = nullptr;
					}
				}						
			}
			if (vehicle != nullptr) {
				delete vehicle;
				vehicle = nullptr;
			}
		}
	}

	void  Parking::returnVehicle() {
		cout << "Return Vehicle" << endl;
		
		char plate[10];
		bool check = false;
		bool found = false;
		 
			do {
				cout << "Enter Licence Plate Number: ";
				cin >> plate;
				
				if (strlen(plate) > 8 || strlen(plate) < 1) {
					
					cout << "Invalid Licence Plate, try again: ";
				}
				else {
					check = true;
				}
				cout << endl;
			} while (!check);

			for (unsigned int i = 0; i < strlen(plate); i++) {
				plate[i] = toupper(plate[i]);
			}
		
			for (int i = 0; i < m_noSpots&& found==false; i++) {

				if (parkingSpot[i]!=nullptr&&*parkingSpot[i]==plate) {
					found = true;
					

					parkingSpot[i]->setCsv(false);
					cout << "Returning: \n";
					parkingSpot[i]->write(std::cout);
					cout << endl;
					delete parkingSpot[i];
					parkingSpot[i] = nullptr;
					m_noPaked--;
		            }			
				    else if(i==(m_noSpots-1)){
						cout << "License plate " << plate << " Not found\n";
					}
				}
			}
		
	

	void Parking::listVehicle() {
		cout << "*** List of parked vehicles ***" << endl;
		
			for (int i = 0; i < m_noSpots; i++) {
				if (parkingSpot[i] != nullptr) {
					
					parkingSpot[i]->setCsv(false);
					parkingSpot[i]->write(std::cout);

					cout << "-------------------------------\n";
								
			}
		}
	}

	bool  Parking::closeParking(){
		bool check = false;
		if (m_noPaked==0) {
			cout << "Closing Parking\n";
			return true;
		}
		else {
			cout << "This will Remove and tow all remaining vehicles from the parking!\n";
			cout << "Are you sure? (Y)es/(N)o: ";
			char option[8];
			
			do {
				cin>>option;
				
				if ((option[0] != 'Y' && option[0] != 'y' && option[0] != 'N' && option[0] != 'n') ||strlen(option)>1) {
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
				else{

					check = true;
				}
				cin.clear();

				cin.ignore(1000, '\n');

			} while (!check);

			if (option[0] == 'Y' || option[0] == 'y') {
				cout << "Closing Parking\n";
				
				for (int i = 0; i < m_noSpots; i++) {
					if (parkingSpot[i] != nullptr) {
						cout << endl;
						cout << "Towing request\n";
						cout << "*********************\n";
						parkingSpot[i]->setCsv(false);
						parkingSpot[i]->write(std::cout);

						delete parkingSpot[i];
						parkingSpot[i] = nullptr;
					}
					
				}
				return true;
			}
			else {
				cout << "Aborted!" << endl;
				return false;
			}
		}
	}

	bool  Parking::exitParking()const {
		
		bool check = false;
		char choice;
		char* option = nullptr;
		cout << "This will terminate the program!" << endl;
		cout << "Are you sure? (Y)es/(N)o: ";

		option = new char[8];
		do {
			cin >> option;

			if ((option[0] != 'Y' && option[0] != 'y' && option[0] != 'N' && option[0] != 'n') || strlen(option) > 1) {
				cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			}

			else {
				check= true;
			}
			cin.clear();
			cin.ignore(1000, '\n');

		} while (!check);

		cout << "Exiting program!" << endl;

		choice = tolower(option[0]);
		delete[] option;
		option = nullptr;
		return choice == 'y';
	}

	bool  Parking::loadDataFile(){
		bool load = false;
		bool check = false;
		bool same = false;
		Vehicle* vehicle=nullptr;
		char cap= '\0';
		int number=0;
		std::ifstream inFile("ParkingData.csv.bak");
		if (!isEmpty()) {
			load = true;			
			if (inFile.fail()) inFile.clear();
			if (inFile.is_open()) inFile.close();
			
			inFile.open(m_dataFileName, ios::in);
			 if(inFile){
				
				do{
				vehicle = nullptr;
				cap = '\0';
				inFile.get(cap);
				inFile.ignore(8, ',');
				
					if (toupper(cap) == 'M') {

						vehicle = new Motorcycle();
						check = true;
					
					}else
					if (toupper(cap) == 'C') {
						vehicle = new Car();
						check = true;
					}
								
				if(check){
					vehicle->setCsv(true);
					vehicle->read(inFile);
					if (vehicle != nullptr/* && !(*vehicle == Vehicle())*/) {
						int n = vehicle->getParkingSpot();
						parkingSpot[(n - 1)] = vehicle;
						m_noPaked++;
						load = true;
						vehicle = nullptr;
						}
					else {
						delete vehicle;
						vehicle = nullptr;
						load = false;
						}
					}
				check = false;
				number++;
				} while (number<m_noSpots&&load==true);
			}
		}
		else {
			load=true;
		}
		for (int i = 0; i < m_noSpots && !same; i++) {
			if (vehicle != nullptr && *vehicle == *parkingSpot[i]) {
				same = true;
			}
		}
		if (!same && vehicle != nullptr) {
			delete vehicle;
			vehicle = nullptr;
		}
		inFile.close();
		return load;
	}

	void  Parking::saveDataFile()const {
		if (!isEmpty()) {			
			ofstream fout("ParkingData.csv.bak");

			if (fout.fail()) fout.clear();
			if (fout.is_open()) fout.close();
			
			fout.open(m_dataFileName, ios::out);
			if(fout.is_open()){
				for (int i = 0; i < m_noSpots; i++) {
					if (parkingSpot[i] != nullptr) {
						parkingSpot[i]->setCsv(true);
						parkingSpot[i]->write(fout);
					}
				}
					fout.close();
			}
		}
	}

	int  Parking::run() {
		
		int option = 0;
		if (!isEmpty()) {
			do {				
				parkingStatus();
				mainMenu->display();
				cin >> option;
				if (option == 1) {
				 parkVehicleMenu();
				}
				else
					if (option == 2) {
						returnVehicle();
					}
					else
						if (option == 3) {
							listVehicle();
						}
						else
							if (option == 4) {
								if (closeParking()) {
									break;
								}
							}
							else
								if (option == 5) {
									exitParking();
									break;
								}
				
			} while (true);
			
		}
		if (m_dataFileName== nullptr) {
			return 1;
		}
		else {
			return 0;
		}
	}

	Parking::operator bool() const {
		return m_dataFileName != nullptr;
	}
}
