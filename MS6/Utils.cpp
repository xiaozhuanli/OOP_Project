/* Citation and Sources...
Final Project Milestone 2
Module: Parking
Filename: Parking.h
Version 1.0
Author	 Xiaozhuan Li(OOP244NAA 162683189)
Revision History
-----------------------------------------------------------
Date      Reason
2020/03/13  Preliminary release
2020/03/16
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdio.h>
#include "Utils.h"

using namespace std;
namespace sdds {
	void clearKeyboard(void)
	{
		while (getchar() != '\n');
	}

	int yes(void)
	{
		char confirm = 'n', NL = '\0';
		int option = 0;

		cin >> confirm;
		if (confirm != '\n')
			NL = getchar();
		if (NL != '\n' && NL != '\0')
			clearKeyboard();
		while (NL != '\n' || (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n'))
		{
			printf("Invalid response, only (Y)es or (N)o are acceptable, retry: ");
			cin >> confirm;
			if (confirm != '\n')
				NL = getchar();
			if (NL != '\n' && NL != '\0')
				clearKeyboard();
		}
		if (confirm == 'Y' || confirm == 'y') option = 1;
		else option = 0;

		return option;
	}
}