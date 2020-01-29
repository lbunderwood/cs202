// Luke Underwood
// 1/28/2020
// cs201
// Spelunking
// Cave.h

#ifndef CAVE_H
#define CAVE_H

#include<fstream>
#include<vector>
#include<random>
#include<string>

class Cave
{
public:

	//Constructor automatically builds cave
	Cave();
	
	//Returns current room's number
	int getCurrentRoom();
	
	//Changes position
	void goToRoom(int room);
	
	//moves player to adjacent room 0, 1, or 2
	void goToAdjacentRoom(int room);
	
	//make two rooms adjacent
	void connect(int room1, int room2);
	
	//prints the short description
	void printShortDesc(int room) const;
	
	//prints the long description
	void printLongDesc(int room) const;
	
	//save rooms to an output stream
	void saveRooms(std::ostream & os) const;
	
	//read rooms from an input stream
	void readRooms(std::istream & is);
	
private:
	struct Room
	{
		int roomNumber_;
		std::string shortDesc_;
		std::string longDesc_;
		std::vector<int> adjacentRooms_;
	
		Room(int roomNum);
	};

	int currentRoom_ = 0;
	std::vector<Room> caveRooms_;
};

#endif CAVE_H