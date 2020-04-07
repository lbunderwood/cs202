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
	std::cout << "INPUT ERROR: Please enter three integer arguments.\n"
		"The first will be the term that the fibonacci and factorial are\n"
		"calculated to, while the second and third will be m and n for the\n"
		"ackermann's, respectively.";
}

int main(int argc, char** argv)
{
	// get command line input
	std::pair<int, int> n;
	if (argc == 2)
	{
		for 
		std::istringstream iss(argv[1]);
		if (!(iss >> n.first))
		{
			inputError();
			return 0;
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
	auto ackR = ack(n[1], n[2]);		// calculate fib the slow way
	ackTime.end();						// stop the clock

	std::cout << "Ackermann's complete!" << std::endl << std::endl;

	// output all this garbage
	std::cout << "For term " << n[0] << ",\n"
		<< "Slow Recursive Fibonacci produced: " << fibSlow
		<< " In " << fibSlowTime.getDuration() << "s.\n"
		<< "Fast Recursive Fibonacci produced: " << fibFast.first
		<< " In " << fibFastTime.getDuration() << "s.\n"
		<< "Non-Recursive Fibonacci produced: " << fibLoop
		<< " In " << fibLoopTime.getDuration() << "s.\n"
		<< "Recursive Factorial produced: " << factSlow
		<< " In " << factSlowTime.getDuration() << "s.\n"
		<< "Non-Recursive Factorial produced: " << factLoop
		<< " In " << factLoopTime.getDuration() << "s.\n"
		<< "For A( " << n[1] << ", " << n[2] << " ),\n"
		<< "Recursive Ackermann's produced: " << ackR
		<< " In " << ackTime.getDuration() << "s.\n";
		
}