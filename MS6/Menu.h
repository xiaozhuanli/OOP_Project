/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.h
Version 1.0
Author	 Xiaozhuan Li(OOP244NAA 162683189)
Revision History
-----------------------------------------------------------
Date      Reason
2020/03/02  Preliminary release
2020/03/09  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream> 
using namespace std;
namespace sdds {
	const int MAX_NO_OF_ITEMS = 10;
	class Menu;
	class MenuItem {
		char* m_content;
		MenuItem() = default;
		~MenuItem();
		MenuItem(const char*);
		MenuItem(const MenuItem&) = delete;
		MenuItem& operator=(const MenuItem&) = delete;
		void display() const;
		friend class Menu;
	};

	class Menu {
		char* m_titleofMenu;
		MenuItem* m_menuItem[MAX_NO_OF_ITEMS];
		int m_numberofItem;
		int m_indent;
	public:
		Menu();
		Menu(const char*, int indent = 0);
		~Menu();
		Menu(const Menu&);
		Menu& operator=(const Menu&);
		operator bool() const;
		bool isempty() const;
		const ostream& display(std::ostream& os = std::cout) const;
		const Menu& operator=(const char*);
		void add(const char*);
		Menu& operator<<(const char* m_content);
		int run() const;
		operator int() const;
		void setsafeEmptyStatus();
	};
}
#endif 
