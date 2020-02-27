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
		std::cout << "There was a game in progress. Continuing...\n";
		fin.close();
		return;
	}
	else //otherwise, we build the cave system
	{
		//in case read was partially completed, the partial data needs to be reset
		fin.close();
		caveRooms_.clear();
		currentRoom_ = 0;


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
		for (int i = 0; i < 15; i++) //for each room,
		{

			//for each of the not already assigned adjacent rooms
			for (int j = getAdjacent(i).size(); j < 3; j++)
			{
				if (i == 14) continue;
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

				//every once in a great while, we get stuck in this do/while,
				//so this is here to prevent that
				unsigned int count = 0;
				//generates random numbers until we get a good one to connect
				do
				{
					room = dist(gen);

					//since we're counting up as we make connections, we don't
					//want to connect to any rooms lower than this one. This
					//if statement saves the do/while many iterations
					if (room < i)
					{
						room += 14 - i;
					}

					count++;
				} while ((getAdjacent(room).size() == 3
					|| room == i
					|| areConnected(i, room))
					&& count < 1000);

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
				caveRooms_[i].shortDesc_ = "You feel a breeze.";
				caveRooms_[i].longDesc_ = "The room is a bottomless pit! You "
					"charge in blindly, falling to your death.";
				caveRooms_[i].pit = true;
				break;

			default: //////// NO HAZARD /////////
				resetRoom(i);
				break;
			}
		}

		// insert the wumpus in a reasonable location
		moveWumpus(0);
	}
}

//Constructor to create room
Cave::Room::Room(int roomNum) : roomNumber_(roomNum) {}

//Returns current room's number
int Cave::getCurrentRoom()
{
	return currentRoom_;
}

//Returns the room number the wumpus is in
int Cave::getWumpusRoom()
{
	return wumpusRoom_;
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

//returns vector with current Room.bat .pit and .wumpus
std::vector<bool> Cave::getHazards(int room)
{
	std::vector<bool> hazards;
	hazards.push_back(caveRooms_[room].bat);
	hazards.push_back(caveRooms_[room].pit);
	hazards.push_back(caveRooms_[room].wumpus);
	return hazards;
}

//returns whether the two rooms are connected
bool Cave::areConnected(int room1, int room2)
{
	for (auto n : getAdjacent(room1))
	{
		if (n == room2)
		{
			return true;
		}
	}

	return false;
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

//assigns the Wumpus to a room other than the one passed
void Cave::moveWumpus(int room)
{
	// loop until we insert the wumpus in a reasonable location
	while (true)
	{
		//generates room numbers randomly
		std::random_device r;
		std::mt19937 gen(r());
		std::uniform_int_distribution<> dist(0, 14);
		int newLocation = dist(gen);

		bool badLocation = false;

		// we don't really want the wumpus in the room it was just in
		// or one adjacent to it (or the start room, for initial placement)
		if (newLocation == room)
		{
			badLocation = true;
		}
		for (auto n : getAdjacent(room))
		{
			if (n == newLocation)
			{
				badLocation == true;
				break;
			}
		}

		// we also don't want it in a room that already has a hazard
		if (caveRooms_[newLocation].bat || caveRooms_[newLocation].pit)
		{
			badLocation = true;
		}

		// if the location is good, put the wumpus there and exit the loop
		if (!badLocation)
		{
			caveRooms_[newLocation].wumpus = true;
			caveRooms_[newLocation].shortDesc_ = "You can smell the wumpus.";
			caveRooms_[newLocation].longDesc_ = "You enter the cave with the Wumpus."
				" It eats you, and you die.";
			resetRoom(wumpusRoom_);
			wumpusRoom_ = newLocation;
			break;
		}
	}
}

//sets room description to default room (after wumpus has left)
void Cave::resetRoom(int room)
{
	//clear short description
	caveRooms_[room].shortDesc_ = "blank";

	// put adjacent room numbers in with nice formatting
	caveRooms_[room].longDesc_ = "You enter room " +
		std::to_string(room) + ". There are tunnels to rooms ";
	for (int j = 0; j < getAdjacent(room).size(); j++)
	{
		caveRooms_[room].longDesc_ +=
			std::to_string(getAdjacent(room)[j]);
		if (j + 3 == getAdjacent(room).size())
		{
			caveRooms_[room].longDesc_ += ", ";
		}
		else if (j + 2 == getAdjacent(room).size())
		{
			caveRooms_[room].longDesc_ += ", and ";
		}
	}
	caveRooms_[room].longDesc_ += ".";

	// reset all hazards
	caveRooms_[room].bat = false;
	caveRooms_[room].pit = false;
	caveRooms_[room].wumpus = false;
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
	os << "Full Cave System:" << std::endl
		<< currentRoom_ << std::endl 
		<< wumpusRoom_ << std::endl;

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
	std::cout << "No previous game found. Building new cave system...\n";
}

//read rooms from an input stream
bool Cave::readRooms(std::istream& is)
{
	// get two initial numbers
	if (!(is >> currentRoom_ && is >> wumpusRoom_))
	{
		readError();
		return false;
	}

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
			continue;
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