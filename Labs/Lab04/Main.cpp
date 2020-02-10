// Luke Underwood
// 2/4/2020
// cs202
// Lab04
// Main.cpp

#include<fstream>
#include<iostream>
#include<string>
#include<sstream>

bool getInt(int& num)
{
	std::string numStr;
	std::getline(std::cin, numStr);
	std::istringstream instr(numStr);
	instr >> num;

	if (instr)
		return true;
	else
		return false;
}

int main()
{
	std::ifstream istr("A_Modest_Proposal.txt");

	while (istr)
	{
		std::string line;
		std::getline(istr, line);
		std::cout << line << "\n";
	}

	std::cout << "Please enter a line of text to append.\n";
	std::string toAppend;
	std::getline(std::cin, toAppend);

	std::cout << "How many times would you like to repeat it?\n";
	int num = 0;
	while (!getInt(num))
	{
		std::cout << "ENTER AN INTEGER. DUMMY.\n";
	}

	std::ofstream ostr("A_Modest_Proposal.txt", std::ios::app);
	for (int i = 0; i < num; i++)
	{
		ostr << toAppend << std::endl;
	}
}