/*
 * ocr.h
 *
 *  Created on: March 22, 2014
 *      Author: Patrick Turner
 */

#ifndef OCR_H_
#define OCR_H_

#include <iostream>
#include <fstream>
#include <bitset>

class ocr
{
public:
	ocr();
	virtual ~ocr();

	std::string readLine(std::string stringArray[3]);
	char convertArray(char array[][3]);
	char charSelect(int selection);
	void writeToFile();
	std::string validateAccountNumber(std::string accountNumber);
	int findIllegibleNumber(int number);

	std::ifstream inputFile;
	std::ofstream outputFile;
};

#endif /* OCR_H_ */
