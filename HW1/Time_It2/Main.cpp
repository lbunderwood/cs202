// Luke Underwood
// 1/23/20
// Lab02
// Main.cpp

#include<iostream>
#include<vector>
#include<string>
#include<random>
#include<algorithm>
#include<iomanip>

#include"Timer.h"

//prints an error message for bad arguments. Always followed by a return 0
void inputErr()
{
	std::cout << "ERROR: BAD INPUT. Please enter a single argument that is the"
		<< " number of elements you wish to have in the vector the algorithms"
		<< " are being tested on. This must be a positive integer.";
}

//prints an error message for a failed algorithm
void algErr()
{
	std::cout << "ERROR: ALGORITHM FAILURE. Please disregard results, as they "
		<< "are the result of a faulty execution. Simply try again.";
}


int main(int argc, char** argv)
{
	//Create a timer to record the full process
	Timer totalTime;

	//Take a command line argument and store it as int elements to determine
	//set size. Plus error handling.
	int elements;
	if (argc == 2)
	{
		elements = std::stoi(argv[1]);
		if (elements <= 0)
		{
			inputErr();
			return 0;
		}
	}
	else
	{
		inputErr();
		return 0;
	}

	//Set up random number generator to create our test set, and a target index
	//of an element that our search algorithms will look for
	std::random_device r;
	std::mt19937 gen(r());
	std::uniform_real_distribution<> dist(0, 100);
	std::uniform_int_distribution<> dist2(0, elements-2);
	int targetIndex = dist2(gen);

	//This is our set
	std::vector<double> set;
	set.reserve(elements);

	//This timer will record how long our set took to create
	Timer setCreation;

	//create the set
	for (int i = 0; i < elements; i++)
	{
		set.push_back(dist(gen));
	}

	//set is created, so stop the timer!
	setCreation.end();
	std::cout << "Set Created!\n";

	//set up for search algorithm
	std::vector<double> target;
	for (int i = 0; i < 2; i++)
	{
		target.push_back(set[targetIndex + i]);
	}
	std::vector<double>::iterator searchResult = set.end();

	//Time the search algorithm
	Timer searchTime;
	searchResult = std::search(set.begin(), set.end(), target.begin(), target.end());
	searchTime.end();

	//Check to make sure it worked
	if (searchResult == set.end()) algErr();
	else std::cout << "Search Complete!\n";

	//Time sorting the set
	Timer sortTime;
	std::sort(set.begin(), set.end());
	sortTime.end();

	std::cout << "Sort Complete!\n";

	//Time checking the sort
	bool sorted = false;
	Timer checkTime;
	sorted = std::is_sorted(set.begin(), set.end());
	checkTime.end();

	//Print error if not sorted
	if (!sorted) algErr();
	else std::cout << "Sort Check Complete!\n";

	//Set up for binary search
	bool found = false;
	double btarget = set[targetIndex];

	//Time binary search
	Timer bSearchTime;
	found = std::binary_search(set.begin(), set.end(), btarget);
	bSearchTime.end();

	//Check that it worked
	if (!found) algErr();
	else std::cout << "Binary Search Complete!\n";

	//Print the results
	std::cout << "The Results are in!\n"

		<< std::setw(30) << "Set Creation took : " 
		<< std::setw(10) << setCreation.getDuration() << " Seconds.\n"

		<< std::setw(30) << "Search took : " 
		<< std::setw(10) << searchTime.getDuration() << " Seconds.\n"

		<< std::setw(30) << "Binary Search took : " 
		<< std::setw(10) << bSearchTime.getDuration() << " Seconds.\n"

		<< std::setw(30) << "Sort took : " 
		<< std::setw(10) << sortTime.getDuration() << " Seconds.\n"

		<< std::setw(30) << "Checking the sort took : " 
		<< std::setw(10) << checkTime.getDuration() << " Seconds.\n";

	totalTime.end();

	std::cout << std::setw(30) << "Total time : " 
		<< std::setw(10) << totalTime.getDuration() << " Seconds.\n";
}