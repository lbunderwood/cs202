#include"names.h"
#include<iostream>

namespace
{
	std::string name4 = "Jack";
}

void foo()
{
	std::cout << "This is the one in main!" << std::endl;
}

int main()
{
	name::Names names;
	names.printNames();
	std::cout << name4;
	name::foo();
	foo();
}