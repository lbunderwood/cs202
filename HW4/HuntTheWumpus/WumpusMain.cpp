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
	std::cout << "To move, enter an \'m\' followed by the number of the room\n"
		"adjacent to your current room that you would like to move to.\n"
		"To shoot, enter an \'s\' followed by the numbers of the rooms you\n"
		"would like to shoot your arrow through (three rooms, each adjacent \n"
		"to the last (note that just because two rooms are adjacent to you \n"
		"does not mean that they are adjacent to each other)). Separate all \n"
		"letters and numbers in your actions by spaces.\n\nExamples:\nm 3\nM 6"
		"\ns 9 5 2"
		<< std::endl;
}

bool getInput(char& MorS, int& r1, int& r2, int& r3)
{
	// collect our input and put it in a stream to parse it out
	std::string input;
	std::getline(std::cin, input);
	std::istringstream iss(input);

	// if our first two inputs were good...
	if (iss >> MorS && iss >> r1 && r1 < 15)
	{
		// ...and we're moving, then get us out
		if (MorS == 'M' || MorS == 'm')
		{
			return true;
		}
		// ...and we're shooting, then collect the other two inputs and return
		else if (iss >> r2 && iss >> r3 && r2 < 15 && r3 < 15)
		{
			return true;
		}
	}

	return false;
}

int main()
{
	std::string keepPlaying = "";

	while (keepPlaying != "N" && keepPlaying != "n")
	{
		// sometimes cave generation takes a few seconds and we want the user to
		// know something is happening
		std::cout << "\nLoading......" << std::endl << std::endl;

		// initialize cave. Default constructor generates the cave for us
		Cave cave;

		// print welcome message and await response
		std::cout << "\nWelcome to Hunt the Wumpus!" << std::endl << std::endl
			<< "Enter a 0 to quit or press ENTER while in the game for"
			<< " instructions at any time!" << std::endl << std::endl 
			<< "Press ENTER to begin!" << std::endl;
		std::string dummy;
		std::getline(std::cin, dummy);

		// initialize variables for use in the loop
		char moveShoot = 1;
		int room1 = 0;
		int room2 = 0;
		int room3 = 0;

		// loop until the user inputs 0
		while (moveShoot != '0')
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
				std::cout << "\n\nGAME OVER\n\n";
				break;
			}
			// or its a normal cave
			else
			{
				std::cout << cave.getAdjacentHazards(cave.getCurrentRoom())
					<< std::endl << "What would you like to do?" << std::endl;
			}

			// collect input and check if it's good
			if (getInput(moveShoot, room1, room2, room3)
				&& cave.areConnected(room1, cave.getCurrentRoom()))
			{
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
					if (cave.areConnected(room1, room2) 
						&& cave.areConnected(room2, room3))
					{
						// if we hit the wumpus
						if (cave.getHazards(room1)[2]
							|| cave.getHazards(room2)[2]
							|| cave.getHazards(room3)[2])
						{
							std::cout << "You shoot into room ";
							if (cave.getHazards(room1)[2]) std::cout << room1;
							else if (cave.getHazards(room2)[2]) std::cout << room2;
							else if (cave.getHazards(room3)[2]) std::cout << room3;
							std::cout << ", where the Wumpus was sleeping, "
								"killing the beast!\n\nYOU WIN!\n\n";
							break;
						}
						else // if we missed
						{
							std::cout << "Your arrow sails through some empty "
								"rooms, clattering noisily against the far "
								"wall of room " << room3 << ". You hear a "
								"distant rumbling, as the Wumpus, awakened by "
								"your shot, relocates.\n";
							cave.moveWumpus(cave.getWumpusRoom());
						}
					}
					else
					{
						printInstructions();
					}
				}
				else
				{
					printInstructions();
				}
			}
			else if (moveShoot == '{')
			{
				cave.saveRooms(std::cout);
			}
			else if (moveShoot != '0')
			{
				printInstructions();
			}
		}

		keepPlaying = "";
		if (moveShoot != '0')
		{
			std::fstream out("Caves.txt", std::ios::trunc | std::ios::out);
			out.close();
			while (keepPlaying != "Y" && keepPlaying != "y"
				&& keepPlaying != "N" && keepPlaying != "n")
			{
				std::cout << "Would you like to play again? Enter y or n.\n";
				std::getline(std::cin, keepPlaying);
			}
		}
		else
		{
			std::fstream out("Caves.txt");
			cave.saveRooms(out);
			out.close();
			break;
		}
	}
}