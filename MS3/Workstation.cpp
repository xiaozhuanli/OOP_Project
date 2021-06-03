// Name: Xiaozhuan Li
// Seneca Student ID: 162683189
// Seneca email: xli403@myseneca.ca
// Date of completion: 07/12/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"
#include "Utilities.h"

using namespace std;


Workstation::Workstation(const string& str) :Station(str) {}

void Workstation::runProcess(std::ostream& os) {
	if (!m_orders.empty()) m_orders.front().fillItem(*this, os);
}

bool Workstation::moveOrder() {
	bool doMove{ false };
	if (!m_orders.empty()) {
		if (m_orders.front().isItemFilled(this->getItemName())) {
			doMove = true;
			if (m_pNextStation) {
				m_pNextStation->m_orders.push_back(move(m_orders.front()));
				m_orders.pop_front();
			}
		}
	}
	return doMove;
}

void Workstation::setNextStation(Station& station) {
	m_pNextStation = (Workstation*)& station;
}

const Workstation* Workstation::getNextStation() const {
	return m_pNextStation;
}

bool Workstation::getIfCompleted(CustomerOrder& order) {
	bool completed = (m_orders.size() > 0) && m_orders.front().isOrderFilled();
	if (completed) {
		order = move(m_orders.front());
		m_orders.pop_front();
	}
	return completed;
}

void Workstation::display(ostream& os) {
	os << getItemName() << " --> " << (getNextStation() ? 
		getNextStation()->getItemName() : "END OF LINE") << endl;
}

Workstation& Workstation::operator+=(CustomerOrder&& order) {
	m_orders.push_back(move(order));
	return  *this;
}



