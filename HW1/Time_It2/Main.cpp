// Luke Underwood
// 1/23/20
// Lab02
// Main.cpp

#include<iostream>
#include<vector>
#include<string>
#include<deque>
#include<list>
#include<random>
#include<algorithm>
#include<iomanip>
#include<fstream>

#include"Timer.h"

//prints an error message for a failed algorithm
void algErr()
{
	std::cout << "ERROR: ALGORITHM FAILURE. Please disregard results, as they "
		<< "are the result of a faulty execution. Simply try again.";
}

//reads the entire file into a vector
void readToVec(std::vector<std::string>& vec, std::fstream& fin)
{
	std::string line;
	while (!fin.eof())
	{
		std::getline(fin, line);
		vec.push_back(line);
	}
}

//reads the entire file into a list
void readToList(std::list<std::string>& list, std::fstream& fin)
{
	std::string line;
	while (!fin.eof())
	{
		std::getline(fin, line);
		list.push_back(line);
	}
}

//reads the entire file into a vector
void readToStr(std::string& string, std::fstream& fin)
{
	std::string line;
	while (!fin.eof())
	{
		std::getline(fin, line);
		string += line;
	}
}

int main()
{
	//Create a timer to record the full process
	Timer totalTime;

	//Set up to read files
	std::fstream modest("A_Modest_Proposal.txt");
	std::fstream beo("Beowulf.txt");
	std::fstream dracula("Dracula.txt");
	std::fstream fStein("Frankenstein.txt");
	std::fstream monte("Monte_Cristo.txt");
	std::vector<std::string> bookVec;
	std::list<std::string> bookList;
	std::string bookString;

	//Time reading books into vector
	Timer createVecTime;
	readToVec(bookVec, modest);
	readToVec(bookVec, beo);
	readToVec(bookVec, dracula);
	readToVec(bookVec, fStein);
	readToVec(bookVec, monte);
	createVecTime.end();

	//Time reading into a list
	Timer createListTime;
	readToList(bookList, modest);
	readToList(bookList, beo);
	readToList(bookList, dracula);
	readToList(bookList, fStein);
	readToList(bookList, monte);
	createListTime.end();

	//Time reading into a string
	Timer createStringTime;
	readToStr(bookString, modest);
	readToStr(bookString, beo);
	readToStr(bookString, dracula);
	readToStr(bookString, fStein);
	readToStr(bookString, monte);
	createStringTime.end();

	//Set up random number generator to create a target index
	//of an element that our search algorithm will look for
	std::random_device r;
	std::mt19937 gen(r());
	std::uniform_int_distribution<> dist(0, bookVec.size());
	int targetIndex = dist(gen);

	//set up for search algorithm
	std::string target = bookVec[targetIndex];
	std::vector<std::string>::iterator searchResult = bookVec.end();

	//Time the search algorithm on the vector
	Timer searchVecTime;
	searchResult = std::search(bookVec.begin(), bookVec.end(), target.begin(), target.end());
	searchVecTime.end();

	//Check to make sure it worked
	if (searchResult == bookVec.end()) algErr();
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