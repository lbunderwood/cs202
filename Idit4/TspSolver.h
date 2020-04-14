// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 2
// Iditarod #4
// TspSolver.h
// TspSolver class header

#ifndef TSPSOLVER_H
#define TSPSOLVER_H

#include "CityList.h"
#include "CityPath.h"

class TspSolver
{
public:

	TspSolver();
	~TspSolver();

	CityPath solveGreedy(int start);
	void bestGreedy();

	void solveRandom();

	void solveMinWeghtTree();

private:

	CityList cities_;

	std::vector<CityPath> paths_;
	std::vector<double> totalDistances_;

};

#endif