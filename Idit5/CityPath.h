// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 2
// Iditarod #3
// CityPath.h
// CityPath class header

#ifndef CITYPATH_H
#define CITYPATH_H

#include<vector>

class CityPath
{
public:

	CityPath();
	CityPath(std::vector<int> path);
	CityPath(int length);
	~CityPath();

	void push_back(int cityNum);

	int getCity(int pathPos) const;

	std::vector<int> getPath() const;

	size_t size() const;

private:

	std::vector<int> path_;

};

#endif