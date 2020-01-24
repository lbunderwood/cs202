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

void printList(std::vector<std::string> fav, std::vector<int> numbers, int counter)
{
	std::cout << "We will order:\n";
	for (int i = 0; i < counter - 2; i++)
	{
		std::cout << numbers[i] << " " << fav[i] << " jump suits" << std::endl;
	}
}

int main()
{
	std::cout << "Please enter some of your favorite colors. Enter \"END\" when done.\n";
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

	std::cout << "Please enter some numbers.\n";
	std::vector<int> numbers;
	int num;

	for (auto n : fav)
	{
		while (!getInt(num))
		{
			std::cout << "Please enter an integer: ";
		}
		numbers.push_back(num);
	}

	printList(fav, numbers, counter);

	while(true)
	{
		int menuchoice = 0;
		std::cout << "What would you like to do? Enter a number to decide\n"
			<< "\t1. See list again\n\t2. Exit program\n";
		getInt(menuchoice);
		switch (menuchoice)
		{
		case 1:
			printList(fav, numbers, counter);
			break;
		case 2:
			return 0;
			break;
		}
	}

	return 0;
}