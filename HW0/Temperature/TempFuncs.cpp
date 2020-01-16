// Created by Luke Underwood
// 1/16/2020
// cs202
// Temperature
// TempFuncs.cpp

#include"TempHead.h"
#include<cstdlib>
#include<iostream>

double c_ftoc(const char* f)
{
	char* end = (char*)f;
	while (*end != '\0')
	{
		end++;
	}
	double fNum = strtod(f, &end);
	return (fNum - 32.0) * (5.0 / 9.0);
}

double c_ctof(const char* c)
{
	char* end = (char*)c;
	while (*end != '\0')
	{
		end++;
	}
	double cNum = strtod(c, &end);
	return (cNum * (9.0 / 5.0)) + 32.0;
}

void inputError()
{
	std::cout << "Invalid arguments. Please enter ftoc or ctof to choose"
		<< " your conversion, followed by the temperature to convert.";
}