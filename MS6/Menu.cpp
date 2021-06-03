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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Menu.h"

using namespace std;
namespace sdds {
	MenuItem::~MenuItem() {
		delete[] m_content;
		m_content = nullptr;
	}

	MenuItem::MenuItem(const char* content) {
		if (content == nullptr) {
			m_content = nullptr;
		}
		else {
			m_content = new char[strlen(content) + 1];
			strcpy(m_content, content);
		}
	}

	void MenuItem::display() const {
		if (m_content != nullptr)
			cout << m_content << endl;
	}

	Menu::Menu() {
		m_titleofMenu = nullptr;
		m_menuItem[0] = nullptr;
		m_numberofItem = 0;
		m_indent = 0;
	}

	Menu::Menu(const char* titleofMenu, int indent) {
		if (titleofMenu != nullptr) {
			m_titleofMenu = new char[strlen(titleofMenu) + 1];
			strcpy(m_titleofMenu, titleofMenu);
			m_indent = indent;
			*m_menuItem = nullptr;
			m_numberofItem = 0;
		}
		else {
			m_titleofMenu = nullptr;
			*this = Menu();
		}
	}

	Menu::~Menu() {
		delete[] m_titleofMenu;
		m_titleofMenu = nullptr;
		for (int i = 0; i < m_numberofItem; ++i) {
			delete m_menuItem[i];
			m_menuItem[i] = nullptr;
		}
	}

	Menu::Menu(const Menu& newMenu) :m_menuItem{} {
		m_numberofItem = newMenu.m_numberofItem;
		m_indent = newMenu.m_indent;
		if (newMenu.m_titleofMenu != nullptr) {
			m_titleofMenu = new char[strlen(newMenu.m_titleofMenu) + 1];
			strcpy(m_titleofMenu, newMenu.m_titleofMenu);
			for (int i = 0; i < newMenu.m_numberofItem; i++) {
				if (newMenu.m_menuItem[i] != nullptr) {
					m_menuItem[i] = new MenuItem(newMenu.m_menuItem[i]->m_content);
				}
				else {
					m_menuItem[i] = nullptr;
				}
			}
		}
		else {
			m_titleofMenu = nullptr;
		}
	}

	Menu& Menu::operator=(const Menu& newMenu) {
		if (this != &newMenu) {
			setsafeEmptyStatus();
			m_numberofItem = newMenu.m_numberofItem;
			m_indent = newMenu.m_indent;
			if (newMenu.m_titleofMenu != nullptr) {
				m_titleofMenu = new char[strlen(newMenu.m_titleofMenu) + 1];
				strcpy(m_titleofMenu, newMenu.m_titleofMenu);
				for (int i = 0; i < newMenu.m_numberofItem; i++) {
					m_menuItem[i] = new MenuItem(newMenu.m_menuItem[i]->m_content);
				}
			}
			else {
				setsafeEmptyStatus();
			}
		}
		return *this;
	}

	Menu::operator bool() const {
		return m_indent >= 0 && m_titleofMenu != nullptr
			&& m_numberofItem > 0 && m_numberofItem <= MAX_NO_OF_ITEMS;
	}

	bool Menu::isempty() const {
		return !(*this);
	}

	const ostream& Menu::display(std::ostream& os) const {
		if (m_titleofMenu == nullptr) {
			os << "Invalid Menu!" << endl;
		}
		else
			if (*m_menuItem == nullptr || m_menuItem[0]->m_content == nullptr) {
				for (int i = 0; i < m_indent; i++) {
					os << "    ";
				}
				os << m_titleofMenu << endl;
				os << "No Items to display!" << endl;
			}
			else {
				for (int i = 0; i < m_indent; i++) {
					os << "    ";
				}
				os << m_titleofMenu << endl;
				for (int i = 0; i < m_numberofItem; i++) {
					if (m_menuItem[i] != nullptr) {
						if (m_menuItem[i]->m_content != nullptr) {
							for (int i = 0; i < m_indent; i++) {
								os << "    ";
							}
							os << i + 1 << "- " << m_menuItem[i]->m_content << endl;
						}
					}
				}for (int i = 0; i < m_indent; i++) {
					os << "    ";
				}
				os << "> ";
			}
		return os;
	}

	const Menu& Menu::operator=(const char* titleofMenu) {
		if (titleofMenu != nullptr) {
			delete[] m_titleofMenu;
			m_titleofMenu = nullptr;
			m_titleofMenu = new char[strlen(titleofMenu) + 1];
			strcpy(m_titleofMenu, titleofMenu);
		}
		else {
			setsafeEmptyStatus();
		}
		return *this;
	}

	void Menu::add(const char* newItem) {
		if (newItem != nullptr) {
			m_menuItem[m_numberofItem] = new MenuItem(newItem);
			m_numberofItem++;
		}
		else {
			setsafeEmptyStatus();
		}
	}

	Menu& Menu::operator<<(const char* newContent) {
		add(newContent);
		return *this;
	}

	int Menu::run() const {
		int num = 0;
		display();
		if (!isempty()) {
			while (true) {
				cin >> num;
				if (cin.fail()) {
					cout << "Invalid Integer, try again: ";
					cin.clear();
					cin.ignore(1000, '\n');
				}
				else {
					if (num >= 1 && num <= m_numberofItem) {
						cin.clear();
						cin.ignore(1000, '\n');
						break;
					}
					else {
						cout << "Invalid selection, try again: ";
						cin.clear();
						cin.ignore(1000, '\n');
					}
				}
			}
		}
		return num;
	}

	Menu::operator int() const {
		return run();
	}

	void Menu::setsafeEmptyStatus() {
		delete[] m_titleofMenu;
		for (int i = 0; i < m_numberofItem; ++i) {
			delete m_menuItem[i];
			m_menuItem[i] = nullptr;
		}
		m_titleofMenu = nullptr;
		m_indent = 0;
		m_numberofItem = 0;
	}
}