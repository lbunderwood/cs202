// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 2
// Iditarod #4
// CityPath.cpp
// CityPath class implementation

#include "CityPath.h"

CityPath::CityPath() {}

CityPath::CityPath(std::vector<int> path)
	: path_(path) {}

CityPath::CityPath(int length)
{
	for (int i = 1; i <= length; i++)
	{
		path_.push_back(i);
	}
}

CityPath::~CityPath() {}

void CityPath::push_back(int cityNum)
{
	path_.push_back(cityNum);
}

int CityPath::getCity(int pathPos) const
{
	return path_[pathPos];
}

std::vector<int> CityPath::getPath() const
{
	return path_;
}

size_t CityPath::size() const
{
	return path_.size();
}