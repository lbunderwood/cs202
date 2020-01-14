// Luke Underwood
// 1/14/2020
// CS202
// Lab01 Main.cpp

#include<iostream>
#include<string>
#include<sstream>
#include<vector>

bool getInt(int& num)
{
	std::string input;
	std::getline(std::cin, input);
	std::istringstream instream(input);
	instream >> num;

	if (instream)
		return true;
	else
		return false;
}

int main()
{
	std::cout << "Please enter some of your favorite things. Enter \"END\" when done.\n";
	int counter = 1;
	std::vector<std::string> fav;
	std::string item;

	do
	{
		std::cout << counter << ": ";
		std::getline(std::cin, item);
		fav.push_back(item);
		counter++;
	} while (item != "END");
	fav.pop_back();

	std::cout << "Please enter three integers.\n";
	std::vector<int> numbers;
	int num;

	for (int i = 0; i < 3; i++)
	{
		std::cout << i + 1 << ": ";
		while (!getInt(num))
		{
			std::cout << "Please enter an integer: ";
		}
		numbers.push_back(num);
	}

	for (auto n : fav)
	{
		std::cout << n << std::endl;
	}
	for (auto n : numbers)
	{
		switch (n)
		{
		case 0:
		case 5:
		case 13:
		case 19:
		case 21:
		case 36:
		case 42:
		case 50:
		case 100:
			std::cout << n << " was one of the special numbers!\n";
			break;
		default:
			std::cout << n << " was not special :(\n";
			break;
		}
	}
	return 0;
}