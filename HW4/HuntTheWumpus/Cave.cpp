// Luke Underwood
// 1/28/2020
// cs201
// Spelunking
// Cave.cpp

#include<iostream>
#include<sstream>

#include "Cave.h"

//Constructor automatically builds cave
Cave::Cave()
{
	std::fstream fin("Caves.txt");
	std::string line;
	
	std::getline(fin, line);

	//if there's already a file with the format we want, use it and move on
	if (line == "Full Cave System:" && readRooms(fin))
	{
		return;
	}
	else //otherwise, we build the cave system
	{
		//in case caveRooms was populated by readRooms at all
		caveRooms_.clear();

		//this will generate random numbers to determine room descriptions and
		//connections randomly
		std::random_device r;
		std::mt19937 gen(r());
		std::uniform_int_distribution<> dist(0, 14);
		int stringNum;

		//creates 15 rooms
		for (int i = 0; i < 15; i++)
		{
			Room thisRoom(i);
			caveRooms_.push_back(thisRoom);
		}

		//this connects the rooms together and assigns descriptions randomly
		int room;
		for (int i = 0; i < 14; i++) //for each room,
		{

			//for each of the not already assigned adjacent rooms
			for (int j = getAdjacent(i).size(); j < 3; j++)
			{

				//this for loop checks to see if all of the connections have
				//already been made. Had to create it in response to an issue
				//where one final room has only 2 connections
				bool allConnectionsMade = false;
				for (auto n : caveRooms_)
				{
					if (n.roomNumber_ != i)
					{
						if (n.adjacentRooms_.size() != 3)
						{
							allConnectionsMade = false;
							break;
						}
						else
						{
							allConnectionsMade = true;
						}
					}
				}

				//if we got all the way through the loop and allConnectionsMade
				//wasn't set to false, we get out of here
				if (allConnectionsMade == true)
				{
					break;
				}

				//bool to see if the two rooms already have been connected once
				bool alreadyConnected = false;

				//generates random numbers until we get a good one to connect
				do
				{
					alreadyConnected = false;
					room = dist(gen);

					//since we're counting up as we make connections, we don't
					//want to connect to any rooms lower than this one. This
					//if statement saves the do/while many iterations
					if (room < i)
					{
						room += 14 - i;
					}

					//make sure they aren't already joined
					for (auto n : getAdjacent(i))
					{
						if (n == room)
						{
							alreadyConnected = true;
						}
					}
				} while (getAdjacent(room).size() == 3
					|| room == i
					|| alreadyConnected);

				//only once we find a room that this room doesnt have another
				//connection with, that isn't itself and isn't already full,
				//we actually connect them.
				connect(i, room);
			}

			// now to create room descriptions
			stringNum = dist(gen);

			if (i == 0)
			{
				stringNum = 4;
			}

			switch (stringNum)
			{
			case 0: /////// BATS /////////////
			case 1: 
				caveRooms_[i].shortDesc_ = "You hear a bat.";
				caveRooms_[i].longDesc_ = "There is a giant bat in this room! "
					"It picks you up and brings you to a new room!";
				caveRooms_[i].bat = true;
				break;

			case 2: /////// PIT ///////////////
			case 3:
				caveRooms_[i].shortDesc_ = "You feel a breeze";
				caveRooms_[i].longDesc_ = "The room is a bottomless pit! You "
					"charge in blindly, falling to your death.";
				caveRooms_[i].pit = true;
				break;

			default: //////// NO HAZARD /////////
				caveRooms_[i].shortDesc_ = "";
				caveRooms_[i].longDesc_ = "You enter room " +
					std::to_string(i) + ". There are tunnels to rooms ";

				// put adjacent room numbers in with nice formatting
				for (int j = 0; j < getAdjacent(i).size(); i++)
				{
					caveRooms_[i].longDesc_ +=
						std::to_string(getAdjacent(i)[j]);
					if (j + 3 == getAdjacent(i).size())
					{
						caveRooms_[i].longDesc_ += ", ";
					}
					else if (j + 2 == getAdjacent(i).size())
					{
						caveRooms_[i].longDesc_ += ", and ";
					}
				}
				caveRooms_[i].longDesc_ += ".";
				break;
			}
		}

		// insert the wumpus in a reasonable location
		for (int i = 1; i < caveRooms_.size(); i++)
		{
			bool badLocation = false;

			// we don't really want the wumpus adjacent to the start room
			for (auto n : getAdjacent(0))
			{
				if (n == i)
				{
					badLocation == true;
					break;
				}
			}

			// we also don't want it in a room that already has a hazard
			if (caveRooms_[i].bat || caveRooms_[i].pit)
			{
				badLocation = true;
			}

			// if the location is good, put the wumpus there and exit the loop
			if (!badLocation)
			{
				caveRooms_[i].wumpus = true;
				caveRooms_[i].shortDesc_ = "You can smell the wumpus.";
				caveRooms_[i].longDesc_ = "You enter the cave with the Wumpus."
					" It eats you, and you die.";
				break;
			}
		}
	}
}

//Constructor to create room
Cave::Room::Room(int roomNum) : roomNumber_(roomNum) {}

//Returns current room's number
int Cave::getCurrentRoom()
{
	return currentRoom_;
}

//get adjacent room numbers given a particular room number
std::vector<int> Cave::getAdjacent(int room)
{
	return caveRooms_[room].adjacentRooms_;
}

//returns a string of nearby hazards
std::string Cave::getAdjacentHazards(int room)
{
	std::string hazards = "";
	for (auto n : getAdjacent(room))
	{
		if (caveRooms_[n].bat || caveRooms_[n].pit || caveRooms_[n].wumpus)
		{
			hazards += caveRooms_[n].shortDesc_ + "\n";
		}
	}

	return hazards;
}

//Changes position
void Cave::goToRoom(int room)
{
	currentRoom_ = room;
}

//moves player to adjacent room 0, 1, or 2
void Cave::goToAdjacentRoom(int room)
{
	currentRoom_ = caveRooms_[currentRoom_].adjacentRooms_[room];
}

//make two rooms adjacent
void Cave::connect(int room1, int room2)
{
	caveRooms_[room1].adjacentRooms_.push_back(room2);
	caveRooms_[room2].adjacentRooms_.push_back(room1);
}

//prints the short description
void Cave::printShortDesc(int room) const
{
	std::cout << caveRooms_[room].shortDesc_;
}

//prints the long description
void Cave::printLongDesc(int room) const
{
	std::cout << caveRooms_[room].longDesc_;
}

//save rooms to an output stream
void Cave::saveRooms(std::ostream& os) const
{
	//begin w this so we know the file is good later
	os << "Full Cave System:" << std::endl;

	//cycle through rooms, putting room number, each desc, and each connected
	//room on individual lines
	for (auto n : caveRooms_)
	{
		os << n.roomNumber_ << std::endl << n.shortDesc_ << std::endl 
			<< n.longDesc_ << std::endl;
		for (auto m : n.adjacentRooms_)
		{
			os << m << std::endl;
		}

		if (n.bat)
		{
			os << "true" << std::endl;
		}
		else
		{
			os << "false" << std::endl;
		}
		if (n.pit)
		{
			os << "true" << std::endl;
		}
		else
		{
			os << "false" << std::endl;
		}
		if (n.wumpus)
		{
			os << "true" << std::endl;
		}
		else
		{
			os << "false" << std::endl;
		}
		os << std::endl;
	}
}

//Prints an error message for file input
void readError()
{
	std::cout << "Something went wrong in reading reading some previously "
		<< "saved data. Rebuilding cave system....." << std::endl;
}

//read rooms from an input stream
bool Cave::readRooms(std::istream& is)
{
	//until we hit end of file, read 'em in one room at a time
	while (!is.eof())
	{
		int roomNum;
		std::string placeholder;
		std::getline(is, placeholder);
		std::istringstream in(placeholder);
		in >> roomNum;

		if (placeholder == "")
		{
			break;
		}
		else if (in)
		{
			Room thisRoom(roomNum);

			std::getline(is, thisRoom.shortDesc_);
			std::getline(is, thisRoom.longDesc_);
			int adjacent;
			while(true)
			{
				std::getline(is, placeholder);
				std::istringstream instream(placeholder);
				instream >> adjacent;
				if (placeholder == "" 
					|| placeholder == "true" 
					|| placeholder == "false")
				{
					break;
				}
				else if (instream)
				{
					thisRoom.adjacentRooms_.push_back(adjacent);
				}
				else
				{
					readError();
					return false;
				}
			}

			if (placeholder == "true")
			{
				thisRoom.bat = true;
			}
			else if (placeholder == "false")
			{
				thisRoom.bat = false;
			}
			else
			{
				readError();
				return false;
			}
			std::getline(is, placeholder);
			if (placeholder == "true")
			{
				thisRoom.pit = true;
			}
			else if (placeholder == "false")
			{
				thisRoom.pit = false;
			}
			else
			{
				readError();
				return false;
			}
			std::getline(is, placeholder);
			if (placeholder == "true")
			{
				thisRoom.wumpus = true;
			}
			else if (placeholder == "false")
			{
				thisRoom.wumpus = false;
			}
			else
			{
				readError();
				return false;
			}

			caveRooms_.push_back(thisRoom);
		}
		else
		{
			readError();
			return false;
		}
	}
}
