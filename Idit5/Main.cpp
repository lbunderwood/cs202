// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 2
// Iditarod #4
// Main.cpp
// Contains main function

#include "TspSolver.h"

int main()
{
	TspSolver solver;
	solver.readFile("pr1002.tsp");
	solver.bestRandom();
	solver.bestGreedy();
	solver.solveMinWeghtTree();


}