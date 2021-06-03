// Name: Xiaozhuan Li
// Seneca Student ID: 162683189
// Seneca email: xli403@myseneca.ca
// Date of completion: 07/12/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "Workstation.h"
#include "CustomerOrder.h"

#ifndef _SDDS_LINEMANAGER_HEADER_
#define _SDDS_LINEMANAGER_HEADER_

using namespace std;

class LineManager {
	std::vector<Workstation*> m_AssemblyLine{};
	std::deque<CustomerOrder> m_ToBeFilled{};
	std::deque<CustomerOrder> m_Completed{};
	size_t m_cntCustomerOrder{};
	static size_t count;

public:
	LineManager(const string& str, vector<Workstation*>& station, vector<CustomerOrder>& order);
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations();
	void displayStationsSorted() const;
	deque<Workstation*> sort(const vector<Workstation*>& AssemblyLine)const;

};
#endif