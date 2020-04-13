// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 1
// Iditarod #3
// CityList.h
// CityList class implementation

#include "CityList.h"

#include <fstream>
#include <sstream>
#include <iostream>

CityList::CityList() {}

CityList::~CityList() {}

// function to print an error message
void readError(std::string filename)
{
	std::cout << "ERROR READING FILE " << filename << std::endl;
}

// Reads in given file and populates list_
void CityList::readFile(std::string filename)
{
	// initialize a filestream and a string to take input
	std::ifstream ifs(filename);
	std::string token;

	// Scroll past the metadata until we get to the coordinates
	while (ifs >> token && token != "NODE_COORD_SECTION") {}

	// check that we exited the loop for the right reason
	if (token != "NODE_COORD_SECTION")
	{
		readError(filename);
		return;
	}

	// initialize a vector to accept the relevant data, and a counter
	std::vector<int> info(3);
	int count = 0;

	// Cycle through until we hit the handy EOF that was placed at the end
	while (ifs >> token && token != "EOF")
	{
		// convert string to int, checking that it worked
		std::istringstream iss(token);
		if (iss >> info[count])
		{
			// if we've reached the appropriate ammount of data, create node
			if (count == 2)
			{
				list_.push_back(CityNode(info[0], info[1], info[2]));
				count = 0;
			}
			// otherwise, increase count
			else count++;
		}
		else
		{
			readError(filename);
			return;
		}
	}

	// check that we exited the loop for the right reason
	if (token != "EOF") readError(filename);
}