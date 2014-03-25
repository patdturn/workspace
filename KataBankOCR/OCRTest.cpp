/*
 * OCRTest.cpp
 *
 *  Created on: March 22, 2014
 *      Author: Patrick Turner
 */

#include "ocr.h"
#include <CppUTest/TestHarness.h>



TEST_GROUP(ocr)
{

};

TEST(ocr,OutputFileIsValid)
{
	ocr classHandler;
	std::string gline;
	std::string eline;
	std::ifstream expectedOutputFile ("expectedoutput.txt");
	std::ifstream generatedOutputFile ("output.txt");

	classHandler.writeToFile();

	while(generatedOutputFile.good())
	{
		std::getline (generatedOutputFile, gline);
		std::getline (expectedOutputFile, eline);
		eline = eline.substr(0,9);
		gline = gline.substr(0,9);

		CHECK(eline.compare(gline) == 0);
	}

	expectedOutputFile.close();
	generatedOutputFile.close();
}

TEST(ocr,ReadInputFileisValid)
{
	ocr classHandler;

	std::string eline = "";
	std::string inputLine = "";
	std::string stringArray[3];
	std::ifstream expectedOutputFile ("expectedoutput.txt");
	std::ifstream inputFile ("expectedoutput1.txt");

	std::getline (expectedOutputFile, eline);
	eline = eline.substr(0,9);

	std::getline (inputFile, stringArray[0]);
	std::getline (inputFile, stringArray[1]);
	std::getline (inputFile, stringArray[2]);

	inputLine = classHandler.readLine(stringArray);

	CHECK(inputLine.compare(eline) == 0);

	expectedOutputFile.close();
	inputFile.close();
}

TEST(ocr,ConvertArrayisValid)
{
	ocr classHandler;
	char testArray[3][3] = {{' ','_',' '},{'|',' ','|'},{'|','_','|'}};

	CHECK('0' == classHandler.convertArray(testArray));
}


TEST(ocr,CharSelectisValid)
{
	ocr classHandler;
	int testIntArray[11] = {175,9,158,155,57,179,183,137,191,187,200};
	char testChar[11] = {'0','1','2','3','4','5','6','7','8','9','?'};

	for(int x = 0; x < 11; x++)
	{
		CHECK(testChar[x] == classHandler.charSelect(testIntArray[x]));
	}
}

TEST(ocr,AccountNumberisValid)
{
	ocr classHandler;
	std::string testString1 = "123456789";
	std::string testString2 = "111111111";
	std::string testString3 = "?23456789";

	CHECK(classHandler.validateAccountNumber(testString1) == "123456789");
	CHECK(classHandler.validateAccountNumber(testString2) == "111111111 ERR");
	CHECK(classHandler.validateAccountNumber(testString3) == "?23456789 ILL");
}

TEST(ocr,FindIllegibleNumber)
{
	ocr classHandler;
	int number = 143;

	CHECK(classHandler.findIllegibleNumber(number) == 0);
}
