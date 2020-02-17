// Luke Underwood
// 2/6/2020
// cs202
// Lab05
// Main.cpp

#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<sstream>

int main()
{
	std::fstream f("data.dat", std::ios::binary | std::ios::in);
	std::vector<int> numbers;
	int number = 0;
	while (true)
	{
		f.read(reinterpret_cast<char*>(&number), sizeof(int));
		if (!f)
		{
			if (f.eof())
			{
				break;
			}
			else throw;
		}
		numbers.push_back(number);
	}

	int numOfNum = numbers.size();
	int total = 0;
	for (auto n : numbers)
	{
		total += n;
	}
	double average = total / numOfNum;
	std::cout << "Number of integers: " << numOfNum << "\nTotal sum: " << total << "\nAverage: " << average;
}