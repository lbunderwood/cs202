// Luke Underwood
// 1/28/2020
// cs201
// Spelunking
// SpelunkMain.cpp

#include<sstream>
#include<iostream>

#include"Cave.h"

bool getInt(int& num)
{
	std::string line;
	std::getline(std::cin, line);
	std::istringstream in(line);
	in >> line;

	if (in)
		return true;
	else
		return false;
}

int main()
{
	Cave cave;

	int menuchoice = -1;

	while (menuchoice != 0)
	{
		cave.printLongDesc(cave.getCurrentRoom);
		std::cout << "Enter one of the numbers below to enter the room "
			<< "described.\nEnter 0 at any time to quit." << std::endl;
			
		for (auto n : cave.getAdjacent(cave.getCurrentRoom))
		{

		}
		while(!getInt(menuchoice))
	}
}