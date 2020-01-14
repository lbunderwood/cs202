// Luke Underwood
// 1/14/2020
// CS202
// Lab01 Main.cpp

#include<iostream>
#include<string>
#include<sstream>

bool getInt(int& num)
{
	std::string input;
	std::getline(std::cin, input);
	std::istringstream instream(input);
	instream >> num;

	if (instream)
	{
		return true;
	}
	return false;
}

int main()
{


	return 0;
}