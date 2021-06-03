// Name: Xiaozhuan Li
// Seneca Student ID: 162683189
// Seneca email: xli403@myseneca.ca
// Date of completion: 07/12/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS

#include "Station.h"
#include "Utilities.h"

using namespace std;

size_t Station::m_widthField=0u;
size_t Station::id_generator=0u;

Station::Station(const string& str) {
	size_t pos{};
	Utilities utility{};	
	bool more{};
	m_id = ++id_generator;
	m_itemName = (utility.extractToken(str, pos, more));
	m_serialNumber = stoi(utility.extractToken(str, pos, more));
	m_quantity = stoi(utility.extractToken(str, pos, more));
	m_widthField = (m_widthField > utility.getFieldWidth()) ? m_widthField : utility.getFieldWidth();
	m_description = (utility.extractToken(str, pos, more));
}

const std::string& Station::getItemName() const {
	return m_itemName;
}

size_t Station::getNextSerialNumber() {
	return m_serialNumber++;
}

size_t Station::getQuantity() const {
	return m_quantity;
}

size_t Station::getID() const {
	return m_id;
}

void Station::updateQuantity() {
	if (m_quantity >= 1) m_quantity--;
	else throw "no more item";
}

void Station::display(std::ostream& os, bool full) const {
	os << '[' << setw(3) << setfill('0') << right << m_id << 
		"] Item: " << setw(m_widthField) << setfill(' ') << left << m_itemName
		<< " [" << setw(6) << setfill('0') << right << m_serialNumber << "]"
		<< setfill(' ') << left;

	if (full) {
		os << " Quantity: " << setw(m_widthField) << m_quantity
		   << " Description: " << m_description;
	}
	os << endl;
}
