// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 1
// Iditarod #3
// CityList.h
// CityList class header

// Copied to Iditarod #4 4/13/2020

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

	// returns list
	std::vector<CityNode> getList() const;

	// returns a node from the list
	CityNode getNode(int node) const;

private:

	std::vector<CityNode> list_;

};

#endif