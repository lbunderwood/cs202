// Luke Underwood
// 2/29/2020
// cs202
// Recursion Problems
// RecursionFuncs.cpp

#include<deque>
#include<utility>

// return term n of the fibonacci, recusrively defined
unsigned long long int fib_slow(int n)
{
	// if fib(n-2) even exists, define recursively
	if (n >= 2) return fib_slow(n - 1) + fib_slow(n - 2);

	//else, return 1
	else return 1;
}

// return term n of the fibonacci, recusrively defined, but the faster way
std::pair<unsigned long long int, unsigned long long int> fib_fast(int n)
{
	// initialize some pairs to hold our stuff
	auto previous = fib_fast(n - 1);

	// if fib(n-2) even exists, define recursively
	if (n >= 2)	return { previous.first + previous.second, previous.first };

	//else, return 1
	else return { 1, 1 };
}

// return term n of the fibonacci, not recursively defined
unsigned long long int fib_loop(int n)
{
	// initialize deque with starting conditions
	std::deque<unsigned long long int> seq = { 1, 1 };

	// define recursively to index n
	for (unsigned int i = 2; i <= n; i++)
	{
		seq.push_back(seq[i - 1] + seq[i - 2]);
		seq.pop_front();
	}

	// return seq[n], not seq.back so that if we asked for 
	// n = 0 or 1 we get the right thing
	return seq.back();
}

// return n factorial, recursively defined
unsigned long long int factorial(int n)
{

}

// return n factorial, not recursively defined
unsigned long long int factorial_loop(int n)
{

}

// return Ackerman's number m,n
unsigned long long int ack(int m, int n)
{

}