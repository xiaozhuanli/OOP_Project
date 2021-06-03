// Name: Xiaozhuan Li
// Seneca Student ID: 162683189
// Seneca email: xli403@myseneca.ca
// Date of completion: 07/12/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "LineManager.h"
#include "Utilities.h"
#include <fstream>
#include <algorithm>

using namespace std;

size_t LineManager::count = 1u;

LineManager::LineManager(const string& str, vector<Workstation*>& station, vector<CustomerOrder>& order) {
	fstream line(str);
	string wsData{}, str1{}, str2{};
	bool doBreak{};
	Utilities::setDelimiter('|');
	Utilities utility{};
	size_t next_pos{};
	bool more{ true };	
	if (!line) {
		throw string("fail to open line document!");
	}
	else 
		while (!line.eof()) {
		more = true;
		doBreak = false;
		getline(line, wsData);
		str1 = utility.extractToken(wsData, next_pos, more);
		if (more) {
			str2 = utility.extractToken(wsData, next_pos, more);
		}
		else 
		{ str2 = ""; }
		for (auto i : station) {
			if (str1 == i->getItemName()) {
				for (auto i1 : station) {
					if (str2 == i1->getItemName()) {
						i->setNextStation(*i1);
						doBreak = 1;
						break;
					}
				}
				if (doBreak)
					break;
			}
		}
	}
	m_AssemblyLine = station;
	m_cntCustomerOrder = order.size();
	m_ToBeFilled = deque<CustomerOrder>(m_cntCustomerOrder);
	for (auto i = 0u; i < m_cntCustomerOrder; i++) {
		m_ToBeFilled[i] = move(order[i]);
	}
}

deque<Workstation*> LineManager::sort(const vector<Workstation*>& AssemblyLine) const {
	deque<Workstation*> sortedLine;
	Workstation* endStation{};
	while (sortedLine.size() != AssemblyLine.size()) {
		for (auto i : AssemblyLine) {
			if (i->getNextStation() == endStation) {
				sortedLine.push_front(i);
				endStation = i;
			}
		}
	}
	return sortedLine;
}

bool LineManager::run(std::ostream& os) {
	CustomerOrder order{};
	deque<Workstation*> AssemblyLineSorted = sort(m_AssemblyLine);
	os << "Line Manager Iteration: " << count << endl;
	if (m_ToBeFilled.size() > 0){
		*AssemblyLineSorted[0] += move(m_ToBeFilled.front());
		m_ToBeFilled.pop_front();
	}

	for (auto i = m_AssemblyLine.begin(); i != m_AssemblyLine.end(); i++) {
		(*i)->runProcess(os);
	}
	for (auto i = m_AssemblyLine.begin(); i != m_AssemblyLine.end(); i++) {

		(*i)->moveOrder();
		if ((*i)->getIfCompleted(order)) {
			m_Completed.push_back(move(order));
		}

	}
	
	count++;

	return m_Completed.size() == m_cntCustomerOrder;
}

void LineManager::displayCompletedOrders(std::ostream& os) const {
	for (auto i = m_Completed.begin(); i != m_Completed.end(); i++) {
		(*i).display(cout);
	}
}

void LineManager::displayStations() {
	for (auto i : m_AssemblyLine) {
		i->display(cout);
	}
}

void LineManager::displayStationsSorted() const {
	deque<Workstation*> sortedLine = sort(m_AssemblyLine);
	for (auto i : sortedLine) {
		i->display(cout);
	}
}


