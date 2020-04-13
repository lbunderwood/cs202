// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 1
// Iditarod #3
// CityList.h
// CityList class header

#ifndef CITYLIST_H
#define CITYLIST_H

#include <vector>
#include <string>
#include "CityNode.h"

class CityList
{
public:

	CityList();
	~CityList();

	// Reads in given file and populates list_
	void readFile(const std::string& fileName);

	// Returns the distance between two nodes
	double distance(int node1, int node2) const;

private:

	std::vector<CityNode> list_;

};

#endif