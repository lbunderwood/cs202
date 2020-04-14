// Luke Underwood
// 4/13/2020
// cs202
// TSPLIB 1
// Iditarod #3
// Main.cpp
// Main function. Tests classes

#include "CityList.h"
#include "CityNode.h"

#include<iostream>
#include<string>
#include<iomanip>
void test(std::string filename)
{
	CityList list;
	list.readFile(filename);

	auto nodes = list.getList();
	std::cout << std::setw(6) << "0" << ": " << std::setw(10)
		<< nodes[0].getCoords().first << std::setw(10)
		<< nodes[0].getCoords().second << std::endl

		<< std::setw(6) << "100" << ": " << std::setw(10)
		<< nodes[100].getCoords().first << std::setw(10)
		<< nodes[100].getCoords().second << std::endl

		<< std::setw(6) << nodes.size() - 2 << ": " << std::setw(10)
		<< nodes[nodes.size() - 2].getCoords().first << std::setw(10)
		<< nodes[nodes.size() - 2].getCoords().second << std::endl

		<< std::setw(6) << nodes.size() - 1 << ": " << std::setw(10)
		<< nodes[nodes.size() - 1].getCoords().first << std::setw(10)
		<< nodes[nodes.size() - 1].getCoords().second << std::endl

		<< "Distance(0, 100) =   " << list.distance(0, 100) << std::endl
		<< "Distance(0, 0) =     " << list.distance(0, 0) << std::endl
		<< "Distance(0, n + 1) = " << list.distance(0, nodes.size()) << std::endl;
}

int main()
{
	test("pr1002.tsp");
	test("pcb1173.tsp");
	test("vm1748.tsp");
	test("rl5915.tsp");
	test("d18512.tsp");
}