// Name: Xiaozhuan Li
// Seneca Student ID: 162683189
// Seneca email: xli403@myseneca.ca
// Date of completion: 07/12/2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

using namespace std;

char Utilities::m_delimiter{ '|' };

void Utilities::setFieldWidth(size_t newWidth) {
	m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const {
	return m_widthField;
}

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	size_t pos = str.find(m_delimiter, next_pos);
	if (pos == next_pos) {
		more = false;
		throw "there are two delimiters with no token";
	}
	else {
		more = (pos != string::npos) ? true : false;
		string tokenExtracted = str.substr(next_pos, pos - next_pos);
		next_pos = pos + 1;
		if (tokenExtracted.size() > m_widthField)
			m_widthField = tokenExtracted.length();
		return tokenExtracted;
	}
	/*if (position != next_pos) {
		more = (position != string::npos) ? true : false;
		string tokenExtracted = str.substr(next_pos, position - next_pos);
		next_pos = position + 1;
		m_widthField = (m_widthField > tokenExtracted.length()) ? m_widthField : tokenExtracted.length();
		return tokenExtracted;
	}
	else {
		more = false;
		throw "there are two delimiters with no token between them";
	}*/
}

void Utilities::setDelimiter(char newDelimiter) {
	m_delimiter = newDelimiter;
}

char Utilities::getDelimiter() {
	return m_delimiter;
}
