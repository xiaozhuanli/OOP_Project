// Name: Xiaozhuan Li
// Seneca Student ID: 162683189
// Seneca email: xli403@myseneca.ca
// Date of completion: 07/12/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "CustomerOrder.h"
#include "Utilities.h"
#include <vector>

using namespace std;

size_t CustomerOrder::m_widthField = 0u;

CustomerOrder::CustomerOrder(string& record) {    
	Utilities utility{};
	size_t next_pos{};
	bool more{};
	vector<string> str{};
    m_name = utility.extractToken(record, next_pos, more);
    m_product = utility.extractToken(record, next_pos, more);
    while (more) {
        str.push_back(utility.extractToken(record, next_pos, more));
    } 
	
    m_cntItem = str.size();
    m_lstItem = new Item * [m_cntItem];
    for (size_t i = 0; i < m_cntItem; i++){
        m_lstItem[i] = new Item(str[i]);
	}
	m_widthField = (m_widthField > utility.getFieldWidth()) ? m_widthField : utility.getFieldWidth();
}

CustomerOrder::CustomerOrder(CustomerOrder& order) {
    throw "not allow copy operations";
}

CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept {
    *this = move(order);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& order) noexcept {
    if (this != &order) {
        if (m_lstItem) {
            for (auto i = 0u; i < m_cntItem; i++) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;
        }

        m_name = order.m_name;
        m_product = order.m_product;
        m_lstItem = order.m_lstItem;
        m_cntItem = order.m_cntItem;
        order.m_name = "";
        order.m_product = "";
        order.m_lstItem = nullptr;
        order.m_cntItem = 0u;
    }
    return *this;
}

CustomerOrder::~CustomerOrder() {
    for (auto i = 0u; i < m_cntItem; i++) {
        delete m_lstItem[i];
    }
    delete[] m_lstItem;
}

bool CustomerOrder::isOrderFilled() const {
    bool isFilled{1};
    for (auto i = 0u; i < m_cntItem; i++) {
        isFilled = isFilled && m_lstItem[i]->m_isFilled;
    }
    return isFilled;
}


bool CustomerOrder::isItemFilled(const std::string& itemName) const {
    bool item{ 1 };
    for (auto i = 0u; i < m_cntItem; i++) {
        if (itemName == m_lstItem[i]->m_itemName) 
			item =item&& m_lstItem[i]->m_isFilled;
    }

    return item;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os) {
	for (auto i = 0u; i < m_cntItem; i++) {
		if (station.getItemName() == m_lstItem[i]->m_itemName) {
			if (station.getQuantity() > 1) {
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				m_lstItem[i]->m_isFilled = true;
				station.updateQuantity();
								
				os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << endl;
			}
			else {
				os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << endl;
			}
		}
	}
}


void CustomerOrder::display(std::ostream& os) const {    
    os << m_name << " - " << m_product << endl;        
    for (auto i = 0u; i < m_cntItem; i++) {
        os << "[" << setw(6) <<right<<setfill('0')<< m_lstItem[i]->m_serialNumber << "] " <<left<< setfill(' ')
            << setw(m_widthField) << m_lstItem[i]->m_itemName << " - "
            << (m_lstItem[i]->m_isFilled ? "FILLED" : "MISSING") << endl;
    }
}

Item** CustomerOrder::getItem() const {
	return m_lstItem;
}

size_t CustomerOrder::get_cntItem() const {
	return m_cntItem;
}

