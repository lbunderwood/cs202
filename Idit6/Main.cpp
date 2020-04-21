// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 2
// Iditarod #4
// Main.cpp
// Contains main function

// Modified 4/20/2020 for Iditarod 5

#include "TspSolver.h"
#pragma comment(lib, "Timer.lib")
int main()
{
	TspSolver solver("pr1002.tsp");
	solver.readFile();
	solver.solve();
}