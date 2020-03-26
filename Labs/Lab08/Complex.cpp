// Luke Underwood
// 3/26/20
// CS202
// Lab08
// Complex.cpp

#include "Complex.h"

double Complex::getReal() const
{
	return real_;
}

double Complex::getComp() const
{
	return complex_;
}

Complex Complex::operator+(Complex rhs)
{
	Complex result(real_ + rhs.getReal(), complex_ + rhs.getComp());
	return result;
}

Complex operator+(double lhs, Complex rhs)
{
	return Complex(lhs + rhs.getReal(), rhs.getComp());
}

Complex operator+(Complex lhs, double rhs)
{

	return Complex(rhs + lhs.getReal(), lhs.getComp());
}

Complex Complex::operator+=(Complex rhs)
{
	*this = *this + rhs;
	return *this;
}

Complex Complex::operator+=(double rhs)
{
	*this = *this + rhs;
	return *this;
}

std::ostream& operator<<(std::ostream& os, Complex comp)
{
	os << comp.getReal() << " + " << comp.getComp() << " * i";
	return os;
}