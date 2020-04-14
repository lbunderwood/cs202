// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 2
// Iditarod #4
// TspSolver.cpp
// TspSolver class implementation

#include "TspSolver.h"

TspSolver::TspSolver() {}

TspSolver::~TspSolver() {}

CityPath TspSolver::solveGreedy(int start)
{
	std::vector<int> unconnected;
	for (int i = 1; i <= cities_.size(); i++)
	{
		if (i != start) unconnected.push_back(i);
	}

	CityPath path;
	path.push_back(start);

	int currentCity = start;

	while (unconnected.size() != 0)
	{
		int shortest = 10000000000;
		int closest = -1;
		int closeIndex = -1;
		for (size_t i = 0; i < unconnected.size(); i++)
		{
			if (cities_.distance(currentCity, unconnected[i]) < shortest)
			{
				shortest = cities_.distance(currentCity, unconnected[i]);
				closest = unconnected[i];
				closeIndex = i;
			}
		}
		unconnected.erase(unconnected.begin() + closeIndex);
		path.push_back(closest);
		currentCity = closest;
	}

	return path;
}

void TspSolver::bestGreedy()
{

}

void TspSolver::solveRandom()
{

}

void TspSolver::solveMinWeghtTree()
{

}