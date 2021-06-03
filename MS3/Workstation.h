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
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

#ifndef _SDDS_WORKSTATION_HEADER_
#define _SDDS_WORKSTATION_HEADER_

using namespace std;

class Workstation :public Station {
    deque<CustomerOrder> m_orders{};
    Workstation* m_pNextStation{};

public:
    Workstation(const string& str);
    Workstation(Workstation&) = delete;
    Workstation& operator=(Workstation&) = delete;
    Workstation(Workstation&&) = delete;
    Workstation& operator=(Workstation&&) = delete;
    void runProcess(std::ostream& os);
    bool moveOrder();
    void setNextStation(Station& station);
    const Workstation* getNextStation() const;
    bool getIfCompleted(CustomerOrder& order);
    void display(std::ostream& os=cout);
    Workstation& operator+=(CustomerOrder&& order);

};
#endif