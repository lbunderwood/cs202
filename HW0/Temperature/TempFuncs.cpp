// Created by Luke Underwood
// 1/16/2020
// cs202
// Temperature
// TempFuncs.cpp

#include"TempHead.h"
#include<cstdlib>

double c_ftoc(const char* f)
{
	char* end = (char*)f;
	while (*end != '\0')
	{
		end++;
	}
	double fNum = strtod(f, &end);
	return (fNum - 32) * (5 / 9);
}

double c_ctof(const char* c)
{
	char* end = (char*)c;
	while (*end != '\0')
	{
		end++;
	}
	double cNum = strtod(c, &end);
	return (cNum - 32) * (5 / 9);
}