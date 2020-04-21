// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 2
// Iditarod #4
// TspSolver.h
// TspSolver class header

// Modified 4/20/2020 for Iditarod 5

#ifndef TSPSOLVER_H
#define TSPSOLVER_H

#include "CityList.h"
#include "CityPath.h"
#include "Timer.h"
#include "SvgCreator.h"

#include<random>

class TspSolver
{
public:

	TspSolver(std::string file);
	~TspSolver();

	CityPath solveGreedy(int start) const;
	void bestGreedy();

	CityPath solveRandom(int start, std::mt19937& gen) const;
	void bestRandom();

	void solveMinWeightTree();

	void readFile();

	void print();

	CityList getCities();

	std::vector<CityPath> getPaths();

	std::vector<double> getDistances();

	std::vector<double> getTimes();

	void solve();

private:

	std::string tspFile_;

	CityList cities_;

	std::vector<CityPath> paths_;
	std::vector<double> totalDistances_;
	std::vector<double> times_;

	SvgCreator creator_;

};

#endif