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

	double getReal() const;

	double getComp() const;

	Complex operator+(Complex rhs);

	Complex operator+=(Complex rhs);

	Complex operator+=(double rhs);

private:

	double real_;
	double complex_;

};

std::ostream& operator<<(std::ostream& os, Complex comp);

Complex operator+(double lhs, Complex rhs);

Complex operator+(Complex lhs, double rhs);

#endif