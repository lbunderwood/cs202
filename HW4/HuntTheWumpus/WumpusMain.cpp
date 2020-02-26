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
		"spaces in your actions by spaces.\n\nExamples:\nm 3\nM 6\ns 9 5 2"
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
	// sometimes cave generation takes a few seconds and we want the user to
	// know something is happening
	std::cout << "Loading......" << std::endl << std::endl;

	// initialize cave. Default constructor generates the cave for us
	Cave cave;

	// print welcome message and await response
	std::cout << "Welcome to Hunt the Wumpus!" << std::endl << std::endl
		<< "Enter a 0 to quit or anything else for instructions at any time!"
		<< std::endl << std::endl << "Press ENTER to begin!" << std::endl;
	std::string dummy;
	std::getline(std::cin, dummy);

	// initialize variables for use in the loop
	char moveShoot = 1;
	int room1 = 0;
	int room2 = 0;
	int room3 = 0;

	// loop until the user inputs 0
	while (moveShoot != 0)
	{
		// print description of current room
		std::cout << std::endl;
		cave.printLongDesc(cave.getCurrentRoom());
		std::cout << std::endl;

		// if there are bats
		if (cave.getHazards(cave.getCurrentRoom())[0])
		{
			std::cout << "Press ENTER to continue";
			std::getline(std::cin, dummy);
			std::random_device r;
			std::mt19937 gen(r());
			std::uniform_int_distribution<> dist(0, 14);
			int newRoom = dist(gen);
			cave.goToRoom(newRoom);
			continue;
		}
		// or a pit or a wumpus
		else if (cave.getHazards(cave.getCurrentRoom())[1] 
			|| cave.getHazards(cave.getCurrentRoom())[2])
		{
			std::cout << "\n\n\nGAME OVER";
			break;
		}
		// or its a normal cave
		else
		{
			std::cout << cave.getAdjacentHazards(cave.getCurrentRoom())
				<< std::endl << std::endl
				<< "What would you like to do?" << std::endl;
		}

		// collect input, telling the user how until they get it right
		while (!(getInput(moveShoot, room1, room2, room3)
			&& cave.areConnected(room1, cave.getCurrentRoom())))
		{
			printInstructions();
		}

		// if we're moving
		if (moveShoot == 'm' || moveShoot == 'M')
		{
			// we already checked that it was adjacent, so just move
			cave.goToRoom(room1);
		}
		// if we're shooting an arrow
		else if (moveShoot == 's' || moveShoot == 'S')
		{
			// if the input was legit
			if (cave.areConnected(room1, room2) && cave.areConnected(room2, room3))
			{
				// if we hit the wumpus
				if (cave.getHazards(room1)[2]
					|| cave.getHazards(room2)[2]
					|| cave.getHazards(room3)[2])
				{
					std::cout << "You shoot into room ";
					if (cave.getHazards(room1)[2]) std::cout << room1;
					if (cave.getHazards(room2)[2]) std::cout << room2;
					if (cave.getHazards(room3)[2]) std::cout << room3;
					std::cout << ", where the Wumpus was sleeping, killing "
						"the beast!\n\nYOU WIN!";
					break;
				}
				else // if we missed
				{
					std::cout << "Your arrow sails through some empty rooms, "
						"clattering noisily against the far wall of room "
						<< room3 << ". You hear a distant rumbling, as the "
						"Wumpus, awakened by your shot, relocates.";
					cave.moveWumpus(room3);
					cave.resetRoom(room3);
				}
			}
		}
	}

	std::fstream out("Caves.txt");
	cave.saveRooms(out);
}