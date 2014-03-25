/*
 * ocr.cpp
 *
 *  Created on: March 22, 2014
 *      Author: Patrick Turner
 */

#include "ocr.h"

ocr::ocr()
{
	ocr::inputFile.open("input.txt");
}

ocr::~ocr()
{
	ocr::inputFile.close();
}

std::string ocr::readLine(std::string stringArray[3])
{
	std::string returnLine = "";
	char charArray[3][3];

	for(int x = 0; x < 9; ++x)
	{
		for(int y = 0; y < 3; ++y)
		{
			charArray[0][y] = stringArray[0][(x*3)+y];
			charArray[1][y] = stringArray[1][(x*3)+y];
			charArray[2][y] = stringArray[2][(x*3)+y];
		}
		returnLine += ocr::convertArray(charArray);
	}

	return ocr::validateAccountNumber(returnLine);
}

char ocr::convertArray(char array[][3])
{
	unsigned int binaryRep = 0;
	int count = 9;
	std::bitset<9> mybits;

	for(int x = 0; x < 3; ++x)
	{
		for(int y = 0; y < 3; ++y)
		{
			if((int)array[x][y] == 32)
			{
				mybits[--count] = 0;
			}
			else
			{
				mybits[--count] = 1;
			}
		}
	}

	binaryRep = mybits.bitset::to_ulong();

	return ocr::charSelect(binaryRep);
}

char ocr::charSelect(int selection)
{
	char returnChar = '?';
	int positionArray[10] = {175,9,158,155,57,179,183,137,191,187};
	char charPosition[10] = {'0','1','2','3','4','5','6','7','8','9'};

	for(int x = 0; x < 10; ++x)
	{
		if(positionArray[x] == selection)
		{
			returnChar = charPosition[x];
		}
		else
		{
			//do nothing
		}
	}

//	if(returnChar == '?')
//	{
//		returnChar = charPosition[ocr::findIllegibleNumber(selection)];
//	}
	return returnChar;
}

void ocr::writeToFile()
{
	std::string stringArray[3];
	std::string blankLine;

	ocr::outputFile.open("output.txt");

	while(ocr::inputFile.good())
	{
		std::getline (ocr::inputFile, stringArray[0]);
		std::getline (ocr::inputFile, stringArray[1]);
		std::getline (ocr::inputFile, stringArray[2]);
		std::getline (ocr::inputFile, blankLine);

		ocr::outputFile << ocr::readLine(stringArray);

		if(!ocr::inputFile.eof())
		{
			ocr::outputFile << "\r\n";
		}

	}

	ocr::outputFile.close();
}

std::string ocr::validateAccountNumber(std::string accountNumber)
{
	std::string returnLine = accountNumber;
	int checkSum = 0;
	int checkSumMultipler = 9;

	if(accountNumber.find("?") != std::string::npos)
	{
		returnLine += " ILL";
	}
	else
	{
		for(int x = 0; x < 9; ++x)
		{
			const char accountChar = accountNumber.c_str()[x];
			checkSum = checkSum + (checkSumMultipler * std::atoi(&accountChar));
			--checkSumMultipler;
		}

		if(checkSum%11 == 0)
		{
			// do nothing
		}
		else
		{
			returnLine += " ERR";
		}
	}

	return returnLine;
}

int ocr::findIllegibleNumber(int number)
{
	int possibleArray[10][7] ={{47,143,167,171,173,174,0},
							   { 1,  8,  0,  0,  0,  0,0},
							   {30,142,150,154,156,  0,0},
							   {27,139,147,153,154,  0,0},
							   {25, 41, 49, 56,  0,  0,0},
							   {51,147,163,177,178,  0,0},
							   {55,151,167,179,181,182,0},
							   { 9,129,136,  0,  0,  0,0},
							   {63,159,175,183,187,189,190},
							   {59,155,171,179,185,186,0}
							  };

	for(int x = 0; x < 10; ++x)
	{
		for(int y = 0; y < 7; ++y)
		{
			if((int)possibleArray[x][y] == number)
			{
				return x;
			}
			else
			{
				// Keep searching
			}
		}
	}

	return number;
}

