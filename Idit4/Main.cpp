// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 2
// Iditarod #4
// Main.cpp
// Contains main function

#include "TspSolver.h"

void run(std::string filename)
{
	TspSolver solver;
	solver.readFile(filename);
	solver.bestRandom();
	solver.bestGreedy();
	solver.solveMinWeghtTree();
	solver.print();
}

int main()
{
	run("pr1002.tsp");
	run("pcb1173.tsp");
	run("vm1748.tsp");
	run("rl5915.tsp");
	run("d18512.tsp");
}