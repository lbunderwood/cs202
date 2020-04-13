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
#include "CityNode.h"

class CityList
{
public:

	CityList();
	~CityList();

private:

	std::vector<CityNode> list_;

};

#endif