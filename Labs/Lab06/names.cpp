#include "names.h"
#include<iostream>

namespace name
{
	Names::Names() : name1_("Joe"), name2_("John"), name3_("Josh") {}

	void Names::printNames()
	{
		std::cout << name1_ << std::endl << name2_ << std::endl << name3_ << std::endl;
	}

	void foo()
	{
		std::cout << "This is within the namespace!" << std::endl;
	}


	std::string name4 = "Luke";
}