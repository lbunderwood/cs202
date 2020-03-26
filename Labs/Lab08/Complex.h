// Luke Underwood
// 3/26/20
// CS202
// Lab08
// Complex.h

#ifndef COMPLEX_H
#define COMPLEX_H

#include<iostream>

class Complex
{
public:

	//----------CONSTRUCTORS----------
	Complex() 
		: real_{ 0 }, complex_{ 0 } {};

	Complex(double real) 
		: real_{ real }, complex_{ 0 } {};

	Complex(double real, double complex) 
		: real_{ real }, complex_{ complex } {};

private:

	double real_;
	double complex_;

};

#endif