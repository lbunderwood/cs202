// Luke Underwood
// 1/28/2020
// cs201
// Spelunking
// SpelunkMain.cpp

#include<sstream>
#include<iostream>

#include"Cave.h"

void printInstructions()
{
	std::cout << "To move, enter an \'m\' followed by the number of the room a"
		"djacent to your current room that you would like to move to. To shoot"
		", enter an \'s\' followed by the numbers of the rooms you would like "
		"to shoot your arrow through (up to three rooms, each adjacent to the "
		"last (note that just because two rooms are adjacent to you does not m"
		"ean that they are adjacent to each other)). Separate all letters and "
		"spaces in your actions by spaces.\n\nExamples:\nm 3\ns 9 5 2"
		<< std::endl;
}

bool getInput(char& MorS, int& r1, int& r2, int& r3)
{
	// collect our input and put it in a stream to parse it out
	std::string input;
	std::getline(std::cin, input);
	std::istringstream iss(input);

	// if our first two inputs were good...
	if (iss >> MorS && iss >> r1)
	{
		// ...and we're moving, then get us out
		if (MorS == 'M' || MorS == 'm')
		{
			return true;
		}
		// ...and we're shooting, then collect the other two inputs and return
		else if (iss >> r2 && iss >> r3)
		{
			return true;
		}
	}

	return false;
}

int main()
{
	std::cout << "Loading......" << std::endl << std::endl;

	Cave cave;

	std::cout << "Welcome to Hunt the Wumpus!" << std::endl << std::endl
		<< "Enter a 0 to quit or anything else for instructions at any time!"
		<< std::endl << std::endl << "Press ENTER to begin!" << std::endl;

	std::string dummy;
	std::getline(std::cin, dummy);

	char moveShoot;
	int room1;
	int room2;
	int room3;

	while (moveShoot != 0)
	{
		std::cout << std::endl;
		cave.printLongDesc(cave.getCurrentRoom());
		std::cout << std::endl 
			<< cave.getAdjacentHazards(cave.getCurrentRoom())
			<< std::endl << std::endl
			<< "What would you like to do?" << std::endl;

		while (!(getInput(moveShoot, room1, room2, room3)
			&& cave.areConnected(room1, cave.getCurrentRoom())))
		{
			printInstructions();
		}

		if (moveShoot == 'm' || moveShoot == 'M')
		{
			cave.goToAdjacentRoom(room1);
		}
	}

	std::fstream out("Caves.txt");
	cave.saveRooms(out);
}