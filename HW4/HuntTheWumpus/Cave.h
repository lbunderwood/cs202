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

	//Returns the room number the wumpus is in
	int getWumpusRoom();

	//get adjacent room numbers given a particular room number
	std::vector<int> getAdjacent(int room);

	//returns a string of nearby hazards
	std::string getAdjacentHazards(int room);

	//returns vector with current Room.bat .pit and .wumpus
	std::vector<bool> getHazards(int room);

	//returns whether the two rooms are connected
	bool areConnected(int room1, int room2);

	//Changes position
	void goToRoom(int room);
	
	//moves player to adjacent room 0, 1, or 2
	void goToAdjacentRoom(int room);

	//assigns the Wumpus to a room other than the one passed
	void moveWumpus(int room);

	//sets room description to default room (after wumpus has left)
	void resetRoom(int room);
	
	//make two rooms adjacent
	void connect(int room1, int room2);
	
	//prints the short description
	void printShortDesc(int room) const;
	
	//prints the long description
	void printLongDesc(int room) const;
	
	//save rooms to an output stream
	void saveRooms(std::ostream & os) const;
	
	//read rooms from an input stream
	bool readRooms(std::istream & is);

private:
	struct Room
	{
		int roomNumber_;
		std::string shortDesc_;
		std::string longDesc_;
		std::vector<int> adjacentRooms_;
		bool bat = false;
		bool pit = false;
		bool wumpus = false;
	
		Room(int roomNum);
	};

	int currentRoom_ = 0;
	int wumpusRoom_ = 0;
	std::vector<Room> caveRooms_;
};

#endif CAVE_H