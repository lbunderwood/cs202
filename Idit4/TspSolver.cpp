// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 2
// Iditarod #4
// TspSolver.cpp
// TspSolver class implementation

#include "TspSolver.h"

#include<random>
#include<vector>

TspSolver::TspSolver() {}

TspSolver::~TspSolver() {}

CityPath TspSolver::solveGreedy(int start) const
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
			double dist = cities_.distance(currentCity, unconnected[i]);
			if (dist < shortest)
			{
				shortest = dist;
				closest = unconnected[i];
				closeIndex = i;
			}
		}

		if (closest == -1 || closeIndex == -1)
		{
			throw;
		}

		unconnected.erase(unconnected.begin() + closeIndex);
		path.push_back(closest);
		currentCity = closest;
	}

	path.push_back(start);

	return path;
}

void TspSolver::bestGreedy()
{
	double shortestDist = 1000000000000;
	CityPath shortest;
	for (int i = 1; i <= cities_.size(); i++)
	{
		CityPath path = solveGreedy(i);
		double dist = cities_.distance(path);
		if (dist < shortestDist)
		{
			shortest = path;
			shortestDist = dist;
		}
	}

	paths_.push_back(shortest);
	totalDistances_.push_back(shortestDist);
}

CityPath TspSolver::solveRandom(int start, std::mt19937& gen) const
{
	std::vector<int> unconnected;
	for (int i = 1; i <= cities_.size(); i++)
	{
		if (i != start) unconnected.push_back(i);
	}

	CityPath path;
	path.push_back(start);

	while (unconnected.size() != 0)
	{
		std::uniform_int_distribution<> distrib(0, unconnected.size() - 1);
		int randIndex = distrib(gen);

		path.push_back(unconnected[randIndex]);
		unconnected.erase(unconnected.begin() + randIndex);
	}

	path.push_back(start);

	return path;
}

void TspSolver::bestRandom()
{
	double shortestDist = 1000000000000;
	CityPath shortest;
	std::random_device r;
	std::mt19937 gen(r());
	for (int i = 1; i <= cities_.size(); i++)
	{
		CityPath path = solveRandom(i, gen);
		double dist = cities_.distance(path);
		if (dist < shortestDist)
		{
			shortest = path;
			shortestDist = dist;
		}
	}

	paths_.push_back(shortest);
	totalDistances_.push_back(shortestDist);
}

void TspSolver::solveMinWeghtTree()
{

}