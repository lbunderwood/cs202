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
#include<queue>
#include<iostream>
#include<iomanip>

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

struct Edge
{
	double dist;
	int city1;
	int city2;

	Edge(double d, int c1, int c2) : dist(d), city1(c1), city2(c2) {}
};


void TspSolver::solveMinWeghtTree()
{
	auto sort = [](Edge edge1, Edge edge2)
	{
		return edge1.dist > edge2.dist;
	};
	std::priority_queue<Edge, std::vector<Edge>, decltype(sort)> edgeQ(sort);
	auto cityVec = cities_.getList();

	for (size_t i = 0; i < cityVec.size(); i++)
	{
		for (size_t j = i + 1; j < cityVec.size(); j++)
		{
			edgeQ.push(Edge(cities_.distance(i, j), i, j));
		}
	}

	std::vector<std::pair<int, int>> edgeVec;
	std::vector<int> degree(cityVec.size(), 0);
	std::vector<int> set(cityVec.size(), -1);

	while (edgeQ.size() > 0)
	{
		int first = edgeQ.top().city1;
		int second = edgeQ.top().city2;
		if (degree[first] < 2 && degree[second] < 2
			&& (set[first] != set[second] || set[first] == -1))
		{
			edgeVec.push_back({ first, second });
			degree[first]++;
			degree[second]++;
			if (set[first] == -1 && set[second] == -1)
			{
				set[first] = first;
				set[second] = first;
			} 
			else if (set[first] == -1 && set[second] != -1)
			{
				set[first] = set[second];
			}
			else if (set[first] != -1 && set[second] == -1)
			{
				set[second] = set[first];
			}
			else
			{
				int setToChange = set[second];
				for (auto& n : set)
				{
					if (n == setToChange)
					{
						n = set[first];
					}
				}
			}
		}
		edgeQ.pop();
	}

	std::pair<int, int> finaledge{ -1,-1 };
	for (size_t i = 0; i < degree.size(); i++)
	{
		if (degree[i] == 1)
		{
			if (finaledge.first == -1)
			{
				finaledge.first = i;
			}
			else if (finaledge.second == -1)
			{
				finaledge.second = i;
			}
			else
			{
				throw;
			}
		}
	}

	if (finaledge.first == -1 || finaledge.second == -1) throw;
	else edgeVec.push_back(finaledge);

	CityPath path;
	path.push_back(1);
	int currentCity = 1;
	while (path.size() < cities_.size())
	{
		for (size_t i = 0; i < edgeVec.size(); i++)
		{
			if (edgeVec[i].first == currentCity)
			{
				path.push_back(edgeVec[i].second);
				currentCity = edgeVec[i].second;
				edgeVec.erase(edgeVec.begin() + i);
				break;
			}
			else if (edgeVec[i].second == currentCity)
			{
				path.push_back(edgeVec[i].first);
				currentCity = edgeVec[i].first;
				edgeVec.erase(edgeVec.begin() + i);
				break;
			}
		}
	}

	path.push_back(1);

	paths_.push_back(path);
	totalDistances_.push_back(cities_.distance(path));
}

void TspSolver::readFile(std::string filename)
{
	cities_.readFile(filename);
}

void TspSolver::print(std::string filename)
{
	for (int i = 0; i < paths_.size(); i++)
	{
		std::cout << filename << " path " << i + 1 << ": " << std::endl;
		for (auto n : paths_[i].getPath())
		{
			std::cout << n << " - ";
		}

		std::cout << "\n\n\tDistance = " << std::setw(7) << totalDistances_[i]
			<< "\n\n---------------------------------------------------\n\n";
	}
}

CityList TspSolver::getCities()
{
	return cities_;
}

std::vector<CityPath> TspSolver::getPaths()
{
	return paths_;
}