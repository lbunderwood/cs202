// Luke Underwood
// 2/29/2020
// cs202
// Recursion Problems
// RecursionMain.cpp

#include <cmath>
#include <sstream>
#include <iostream>
#include <vector>
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
	std::vector<int> n;
	if (argc == 4)
	{
		for (int i = 1; i < 4; i++)
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
	///////    Fibonacci    ////////////
	////////////////////////////////////

	Timer fibSlowTime;					// start the clock
	auto fibSlow = fib_slow(n[0]);		// calculate fib the slow recursive way
	fibSlowTime.end();					// stop the clock

	std::cout << "Fibonacci slow method complete!" << std::endl;

	Timer fibFastTime;					// start the clock
	auto fibFast = fib_fast(n[0]);		// calculate fib the fast recursive way
	fibFastTime.end();					// stop the clock

	std::cout << "Fibonacci fast recursive method complete!" << std::endl;

	Timer fibLoopTime;					// start the clock
	auto fibLoop = fib_loop(n[0]);		// calculate fib the non-recursive way
	fibLoopTime.end();					// stop the clock

	std::cout << "Fibonacci loop method complete!" << std::endl;

	////////////////////////////////////
	///////    Factorial    ////////////
	////////////////////////////////////

	Timer factSlowTime;					// start the clock
	auto factSlow = factorial(n[0]);	// calculate fib the slow way
	factSlowTime.end();					// stop the clock

	std::cout << "Factorial recursive method complete!" << std::endl;

	Timer factLoopTime;						// start the clock
	auto factLoop = factorial_loop(n[0]);	// calculate fib the slow way
	factLoopTime.end();						// stop the clock

	std::cout << "Factorial loop method complete!" << std::endl;

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