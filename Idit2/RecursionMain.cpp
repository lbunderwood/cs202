// Luke Underwood
// 2/29/2020
// cs202
// Recursion Problems
// RecursionMain.cpp

#include <cmath>
#include <sstream>
#include <iostream>
#include <vector>
#include <utility>
#include "RecursionHead.h"
#include "Timer.h"

#pragma comment (lib, "Timer.lib")

void inputError()
{
	std::cout << "INPUT ERROR: Please enter two integer arguments,\n"
		"which will be m and n for the ackermann's.";
}

int main(int argc, char** argv)
{
	// get command line input
	std::vector<int> n;
	if (argc == 3)
	{
		for (int i = 1; i < 3; i++)
		{
			std::istringstream iss(argv[i]);
			int num = 0;
			if (iss >> num)
			{
				n.push_back(num);
			}
			else
			{
				inputError();
				return 0;
			}
		}
	}
	else
	{
		inputError();
		return 0;
	}

	////////////////////////////////////
	///////    Ackerman's    ///////////
	////////////////////////////////////

	Timer ackTime;						// start the clock
	auto ackR = ack(n[0], n[1]);		// calculate fib the slow way
	ackTime.end();						// stop the clock

	std::cout << "Ackermann's complete!" << std::endl << std::endl;

	// output all this garbage
	std::cout << "For n = " << n[0] << ", m = " << n[1] << ",\n"
		<< "Recursive Ackermann's produced: " << ackR
		<< " In " << ackTime.getDuration() << "s.\n";		
}