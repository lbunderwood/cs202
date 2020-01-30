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

		//creates 15 rooms, each with a random desc and adds them to caveRooms_
		for (int i = 0; i < 15; i++)
		{
			Room thisRoom(i);
			stringNum = dist(gen);

			switch (stringNum)
			{
			case 0: //different number of cases = different weighted chance
			case 1: //of getting this desc for a given room
			case 2:
				thisRoom.shortDesc_ = "You hear a faint chirping and rustling.";
				thisRoom.longDesc_ = "The room is full of bats! They were asleep, "
					"but now they are coming awake. Best to leave quickly.";
				break;
			case 3:
				thisRoom.shortDesc_ = "A faint flickering emanates from the room.";
				thisRoom.longDesc_ = "There is a bonfire in the center of the room"
					", with a sword thrust point down into the center of the fire."
					" You get the feeling that many weary SOULS (haha) have rested"
					" here.";
				break;
			case 4:
			case 5:
			case 6:
				thisRoom.shortDesc_ = "You feel a breeze rushing towards this "
					"room.";
				thisRoom.longDesc_ = "The room is nothing but a giant, bottomless "
					"pit! Only a thin ledge provides access to the other rooms.";
				break;
			case 7:
			case 8:
			case 9:
				thisRoom.shortDesc_ = "You notice nothing out of the ordinary.";
				thisRoom.longDesc_ = "The room is shaped like a cube, with "
					"perfectly smooth stone walls and, and no distinguishing"
					" features aside from its complete lack of them.";
				break;
			case 10:
				thisRoom.shortDesc_ = "You notice nothing out of the ordinary.";
				thisRoom.longDesc_ = "There's a dragon, crouched over a pile of "
					" gold, jewels, and other treasures. He's asleep now, with "
					"a faint tendril of smoke rising from his nostrils. Best to"
					" leave while you can.";
				break;
			case 11:
			case 12:
			case 13:
			case 14:
				thisRoom.shortDesc_ = "What you can see of the room looks... "
					"very... cavey";
				thisRoom.longDesc_ = "The room is a very generic cave room. It "
					"has an abundance of stalagmites and stalactites sprouting "
					"from the floor and cieling. A small trickle of water runs "
					"down the far wall, accross the floor, and into a crack near "
					"your feet.";
				break;
			}

			caveRooms_.push_back(thisRoom);
		}

		//this connects the rooms together randomly
		int room;
		for (int i = 0; i < 14; i++) //for each room,
		{
			//for each of the not already assigned adjacent rooms
			for (int j = caveRooms_[i].adjacentRooms_.size(); j < 3; j++)
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
					for (auto n : caveRooms_[i].adjacentRooms_)
					{
						if (n == room)
						{
							alreadyConnected = true;
						}
					}
				} while (caveRooms_[room].adjacentRooms_.size() == 3 || room == i
					|| alreadyConnected);

				//only once we find a room that this room doesnt have another
				//connection with, that isn't itself and isn't already full,
				//we actually connect them.
				connect(i, room);
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
				if (placeholder == "")
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
			caveRooms_.push_back(thisRoom);
		}
		else
		{
			readError();
			return false;
		}
	}
}
