// Name: Xiaozhuan Li
// Seneca Student ID: 162683189
// Seneca email: xli403@myseneca.ca
// Date of completion: 07/12/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#ifndef _SDDS_STATION_HEADER_
#define _SDDS_STATION_HEADER_

using namespace std;

class Station {
	size_t m_id{};
	string m_itemName{};
	string m_description{};
	size_t m_serialNumber{};
	size_t m_quantity{};

	static size_t m_widthField;
	static size_t id_generator;

public:
	Station(const string& str);
	const std::string& getItemName() const;
	size_t getID() const;
	size_t getNextSerialNumber();
	size_t getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
};
#endif
