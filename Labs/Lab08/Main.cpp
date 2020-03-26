// Luke Underwood
// 3/26/20
// CS202
// Lab08
// Main.cpp

#include"Complex.h"

int main()
{
	std::cout << "Demonstrating Constructors: \n"
		<< Complex() << std::endl
		<< Complex(1) << std::endl
		<< Complex(2, 3) << std::endl << std::endl
		<< "Demonstrating addition overloads: \n"
		<< 4 + Complex(5, 6) << std::endl
		<< Complex(7, 8) + 9 << std::endl
		<< Complex(10, 11) + Complex(12, 13) << std::endl << std::endl
		<< "Demonstrating compound assignment: \n";

	for (Complex iterate; iterate.getReal() < 10; iterate += Complex(1, 2))
	{
		std::cout << iterate << std::endl;
	}

	std::cout << std::endl << "And now with just a double: \n";

	for (Complex iterate; iterate.getReal() < 10; iterate += 2.0)
	{
		std::cout << iterate << std::endl;
	}
}