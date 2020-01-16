// Created by Luke Underwood
// 1/16/2020
// cs202
// Temperature
// TempMain.cpp

#include"TempHead.h"
#include<iostream>

int main(int argc, char** argv)
{

	const char* conversion;
	const char* inTemp;
	double outTemp;

	if (argc != 3)
	{
		std::cout << "Invalid arguments. Please enter ftoc or ctof to choose"
			<< " your conversion, followed by the temperature to convert.";
		throw;
	}
	else
	{
		conversion = argv[1];
		inTemp = argv[2];
	}

	if (conversion == "ftoc")
	{
		std::cout << inTemp << " F = " << c_ftoc(inTemp) << " C";
	} 
	else if (conversion == "ctof")
	{
		std::cout << inTemp << " C = " << c_ctof(inTemp) << " F";
	}


}