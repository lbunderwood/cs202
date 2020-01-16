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

	if (argc != 3)
	{
		inputError();
		return 0;
	}
	else
	{
		conversion = argv[1];
		inTemp = argv[2];
	}

	if (!strcmp(conversion, "ftoc"))
	{
		std::cout << inTemp << " F = " << c_ftoc(inTemp) << " C";
	} 
	else if (!strcmp(conversion, "ctof"))
	{
		std::cout << inTemp << " C = " << c_ctof(inTemp) << " F";
	}
	else
	{
		inputError();
		return 0;
	}


}