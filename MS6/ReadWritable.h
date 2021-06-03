/* ------------------------------------------------------
Final Project Milestone 3
Module: ReadWritable
Filename: ms3_RWTester.cpp
Version 1.0
Author	Xiaozhuan Li(OOP244 NAA)
Revision History
-----------------------------------------------------------
Date      Reason
2020/3/23  Preliminary release
2020/3/23
-----------------------------------------------------------*/
#ifndef SDDS_READWRITABLE_H__
#define SDDS_READWRITABLE_H__
#include <iostream>
using namespace std;
namespace sdds {
	class ReadWritable {
		bool commaSeparatedValues;

	public:
		ReadWritable();
		virtual ~ReadWritable();
		bool isCsv()const;
		void setCsv(bool value);
		virtual std::istream& read(std::istream& is = std::cin) = 0;
		virtual std::ostream& write(std::ostream& os = std::cout)const = 0;
	};
	std::ostream& operator<<(std::ostream& os, const ReadWritable& rw);
	std::istream& operator>>(std::istream& is, ReadWritable& rw);
}
#endif 
