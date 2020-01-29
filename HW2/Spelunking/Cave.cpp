// Luke Underwood
// 1/28/2020
// cs201
// Spelunking
// Cave.cpp

#include<iostream>

#include "Cave.h"

//Constructor automatically builds cave
Cave::Cave()
{
	std::fstream fin("Caves.txt");
	std::string line;
	
	fin >> line;

	if (line == "Full Cave System:")
	{
		readRooms(fin);
		return;
	}
	else
	{
		std::random_device r;
		std::mt19937 gen(r());
		std::uniform_int_distribution<> dist(0, 14);
		int stringNum;

		for (int i = 0; i < 15; i++)
		{
			Room thisRoom(i);
			stringNum = dist(gen);

			switch (stringNum)
			{
			case 0:
			case 1:
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
		}

		bool connected = false;
		while (!connected)
		{
			int room1;
			int room2;

			do
			{
				room1 = dist(gen);
				room2 = dist(gen);
			} while (caveRooms_[room1].adjacentRooms_.size() == 3
				|| caveRooms_[room2].adjacentRooms_.size() == 3);

			connect(room1, room2);

			for (int i = 0; i < 15; i++)
			{
				if (caveRooms_[i].adjacentRooms_.size() != 3)
				{
					connected = false;
					break;
				}
				else
				{
					connected = true;
				}
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

}

//read rooms from an input stream
void Cave::readRooms(std::istream& is)
{

}