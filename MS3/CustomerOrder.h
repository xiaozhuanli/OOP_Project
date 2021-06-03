// Name: Xiaozhuan Li
// Seneca Student ID: 162683189
// Seneca email: xli403@myseneca.ca
// Date of completion: 07/12/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <string>
#include "Station.h"

#ifndef _SDDS_CUSTOMERORDER_HEADER_
#define _SDDS_CUSTOMERORDER_HEADER_

using namespace std;

struct Item {
    std::string m_itemName;
    unsigned int m_serialNumber = 0;
    bool m_isFilled = false;
    Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {
    std::string m_name{};
    std::string m_product{};
    unsigned int m_cntItem{};
    Item** m_lstItem{};
    static size_t m_widthField;

public:
    CustomerOrder() = default;
    CustomerOrder(std::string& str);
    CustomerOrder(CustomerOrder&);
    CustomerOrder& operator=(CustomerOrder&) = delete;
    CustomerOrder(CustomerOrder&&) noexcept;
    CustomerOrder& operator=(CustomerOrder&&) noexcept;
    ~CustomerOrder();
    bool isOrderFilled() const;
    bool isItemFilled(const std::string& itemName) const;
    void fillItem(Station& station, std::ostream& os);
    void display(std::ostream& os) const;

	Item** getItem() const;
	size_t get_cntItem() const;
	
};
#endif