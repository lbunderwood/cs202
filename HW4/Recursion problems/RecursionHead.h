// Luke Underwood
// 2/29/2020
// cs202
// Recursion Problems
// RecursionMain.cpp

#include<utility>

#ifndef RECURSIONHEAD_H
#define RECURSIONHEAD_H

// return term n of the fibonacci, recusrively defined
unsigned long long int fib_slow(int n);

// return term n of the fibonacci, recusrively defined, but the faster way
std::pair<unsigned long long int, unsigned long long int> fib_fast(int n);

// return term n of the fibonacci, not recursively defined
unsigned long long int fib_loop(int n);

// return n factorial, recursively defined
unsigned long long int factorial(int n);

// return n factorial, not recursively defined
unsigned long long int factorial_loop(int n);

// return Ackerman's number m,n
unsigned long long int ack(int m, int n);

#endif