// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 1
// Iditarod #3
// CityList.h
// CityList class implementation

// Copied to Iditarod #4 4/13/2020

#include "CityList.h"

#include <fstream>
#include <sstream>
#include <iostream>

CityList::CityList() {}

CityList::~CityList() {}

// function to print an error message
void readError(const std::string& filename)
{
	std::cout << "ERROR READING FILE " << filename << std::endl;
}

// Reads in given file and populates list_
void CityList::readFile(const std::string& filename)
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
	std::vector<double> info(3);
	int count = 0;

	// Cycle through until we hit the handy EOF that was placed at the end
	while (ifs >> token && token != "EOF")
	{
		// put data in info, checking for scientific notation and errors
		if (token.size() > 7 && token.substr(7, 2) == "e+")
		{
			std::istringstream iss1(token.substr(0, 7));
			std::istringstream iss2(token.substr(9, 2));
			int exp;
			if (iss1 >> info[count] && iss2 >> exp)
			{
				info[count] *= pow(10, exp);
			}
			else
			{
				readError(filename);
				return;
			}
		}
		else
		{
			std::istringstream iss(token);
			if (!(iss >> info[count]))
			{
				readError(filename);
				return;
			}
		}

		// if we've reached the appropriate ammount of data, create node
		if (count == 2)
		{
			list_.push_back(CityNode(info[0], info[1], info[2]));
			count = 0;
		}
		// otherwise, increase count
		else count++;
		
	}

	// check that we exited the loop for the right reason
	if (token != "EOF") 
		readError(filename);
}

// Returns the distance between two nodes
double CityList::distance(int node1, int node2) const
{
	// check that node numbers are good
	if (node1 >= list_.size() || node1 < 0 
		|| node2 >= list_.size() || node2 < 0
		|| node1 == node2)
		return 0;

	// return sqrt((x2-x1)^2 + (y2-y1)^2) = euclidian distance
	else return sqrt(
		pow(list_[node2].getCoords().first 
			- list_[node1].getCoords().first, 2)
		+ 
		pow(list_[node2].getCoords().second 
			- list_[node1].getCoords().second, 2));
}

// returns the total distance for a given path
double CityList::distance(const CityPath& path) const
{
	double total = 0;
	auto pathVec = path.getPath();
	for (int i = 1; i < path.size(); i++)
	{
		total += distance(pathVec[i], pathVec[i - 1]);
	}
	return total;
}

// returns list
std::vector<CityNode> CityList::getList() const
{
	return list_;
}

// returns a node from the list
CityNode CityList::getNode(int node) const
{
	return list_[node];
}

size_t CityList::size() const
{
	return list_.size();
}
