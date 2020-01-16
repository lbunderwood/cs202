// Created by Luke Underwood
// 1/16/2020
// cs202
// Temperature
// BookMain.cpp

#include<iostream>
#include<fstream>
#include<string>

int main()
{
	std::ifstream fin("Chaucer.txt");
	std::string line = "";
	while (line != "          BALADE THAT CHAUCIER MADE.")
	{
		std::getline(fin, line);
	}
	while (line != "XXV. COMPLAINT TO MY MORTAL FOE.")
	{
		std::cout << line << std::endl;
		std::getline(fin, line);
	}
}