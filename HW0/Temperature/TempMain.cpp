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

		if (argv[2][0] == '-')
		{
			if (argv[2][1] > '9' || argv[2][1] < '0')
			{

				inputError();
				return 0;
			}
		}
		else if (argv[2][0] > '9' || argv[2][0] < '0')
		{
			inputError();
			return 0;
		}

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