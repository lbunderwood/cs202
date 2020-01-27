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

void reset(std::fstream& fin)
{
	fin.clear();
	fin.seekg(0, fin.beg);
}

int main()
{
	//Create a timer to record the full process
	Timer totalTime;

	/////////////////////  READ  ///////////////////

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
	std::cout << "Books Read to Vector!\n";

	//Reset the fstreams
	reset(modest);
	reset(beo);
	reset(dracula);
	reset(fStein);
	reset(monte);

	//Time reading into a list
	Timer createListTime;
	readToList(bookList, modest);
	readToList(bookList, beo);
	readToList(bookList, dracula);
	readToList(bookList, fStein);
	readToList(bookList, monte);
	createListTime.end();
	std::cout << "Books Read to List!\n";

	//Reset the fstreams
	reset(modest);
	reset(beo);
	reset(dracula);
	reset(fStein);
	reset(monte);

	//Time reading into a string
	Timer createStringTime;
	readToStr(bookString, modest);
	readToStr(bookString, beo);
	readToStr(bookString, dracula);
	readToStr(bookString, fStein);
	readToStr(bookString, monte);
	createStringTime.end();
	std::cout << "Books Read to String!\n";

	///////////////////  SEARCH  //////////////////////
	
	//Set up random number generator to create a target index
	//of an element that our search algorithm will look for
	std::random_device r;
	std::mt19937 gen(r());
	std::uniform_int_distribution<> dist(0, bookVec.size() - 4);
	int targetIndex = dist(gen);

	//set up for search algorithm
	std::vector<std::string>::iterator vecTarget = bookVec.begin() + targetIndex;

	std::list<std::string>::iterator listTargetStart = bookList.begin();
	std::advance(listTargetStart, targetIndex);
	std::list<std::string>::iterator listTargetEnd = listTargetStart;
	std::advance(listTargetEnd, 2);

	std::string::iterator strTarget = bookString.begin() + targetIndex;

	std::vector<std::string>::iterator vecSearchResult = bookVec.end();
	std::list<std::string>::iterator listSearchResult = bookList.end();
	std::string::iterator strSearchResult = bookString.end();

	//Time the search algorithm on the vector
	Timer searchVecTime;
	vecSearchResult = std::search(bookVec.begin(), bookVec.end(), vecTarget, vecTarget + 2);
	searchVecTime.end();

	//Check to make sure it worked
	if (vecSearchResult == bookVec.end()) algErr();
	else std::cout << "Vector Search Complete!\n";
	
	//Time the search algorithm on the list
	Timer searchListTime;
	listSearchResult = std::search(bookList.begin(), bookList.end(), listTargetStart, listTargetEnd);
	searchListTime.end();

	//Check to make sure it worked
	if (listSearchResult == bookList.end()) algErr();
	else std::cout << "List Search Complete!\n";
	
	//Time the search algorithm on the vector
	Timer searchStrTime;
	strSearchResult = std::search(bookString.begin(), bookString.end(), strTarget, strTarget + 2);
	searchStrTime.end();

	//Check to make sure it worked
	if (strSearchResult == bookString.end()) algErr();
	else std::cout << "String Search Complete!\n";
	
	///////////////////  SORT  //////////////////////
	
	//Time sorting the vector
	Timer sortVecTime;
	std::sort(bookVec.begin(), bookVec.end());
	sortVecTime.end();
	std::cout << "Sort Vector Complete!\n";
	
	//Time sorting the list
	Timer sortListTime;
	bookList.sort();
	sortListTime.end();
	std::cout << "Sort List Complete!\n";
	
	//Time sorting the string
	Timer sortStringTime;
	std::sort(bookString.begin(), bookString.end());
	sortStringTime.end();
	std::cout << "Sort String Complete!\n";
	
	////////////////  RESULTS  /////////////////////

	//Print the results
	std::cout << "The Results are in!\n"

		<< std::setw(30) << "Vector Creation took : "
		<< std::setw(10) << createVecTime.getDuration() << " Seconds.\n"

		<< std::setw(30) << "List Creation took : "
		<< std::setw(10) << createListTime.getDuration() << " Seconds.\n"

		<< std::setw(30) << "String Creation took : "
		<< std::setw(10) << createStringTime.getDuration() << " Seconds.\n"

		<< std::setw(30) << "Vector Search took : "
		<< std::setw(10) << searchVecTime.getDuration() << " Seconds.\n"

		<< std::setw(30) << "List Search took : "
		<< std::setw(10) << searchListTime.getDuration() << " Seconds.\n"

		<< std::setw(30) << "String Search took : "
		<< std::setw(10) << searchStrTime.getDuration() << " Seconds.\n"
		
		<< std::setw(30) << "Vector Sort took : "
		<< std::setw(10) << sortVecTime.getDuration() << " Seconds.\n"
		
		<< std::setw(30) << "List Sort took : "
		<< std::setw(10) << sortListTime.getDuration() << " Seconds.\n"
		
		<< std::setw(30) << "String Sort took : "
		<< std::setw(10) << sortStringTime.getDuration() << " Seconds.\n";
		
	totalTime.end();

	std::cout << std::setw(30) << "Total time : " 
		<< std::setw(10) << totalTime.getDuration() << " Seconds.\n";
}