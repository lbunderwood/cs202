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
	in >> num;

	if (in)
		return true;
	else
		return false;
}

int main()
{
	std::cout << "Loading......" << std::endl << std::endl;

	Cave cave;

	std::cout << "Welcome to Spelunking in C++!" << std::endl << std::endl
		<< "Press ENTER to begin!" << std::endl;

	std::string dummy;
	std::getline(std::cin, dummy);

	int menuchoice = -1;

	while (menuchoice != 0)
	{
		std::cout << std::endl;
		cave.printLongDesc(cave.getCurrentRoom());
		std::cout << std::endl << std::endl 
			<< "Enter one of the numbers below to enter the room "
			<< "described.\nEnter 0 at any time to quit." << std::endl;
			
		for (int i = 0; 
			i < cave.getAdjacent(cave.getCurrentRoom()).size(); i++)
		{
			std::cout << "\t" << i + 1 << ". ";
			cave.printShortDesc(cave.getAdjacent(cave.getCurrentRoom())[i]);
			std::cout << std::endl;
		}

		while (!getInt(menuchoice) || menuchoice > 3 || menuchoice < 0)
		{
			std::cout << "Please enter an integer corresponding to one of the"
				<< " menu options." << std::endl;
		}

		if(menuchoice != 0) cave.goToAdjacentRoom(menuchoice - 1);
	}

	std::fstream out("Caves.txt");
	cave.saveRooms(out);
}