// Luke Underwood
// 2/10/2020
// cs202
// HW2
// Tokenizer
// Tokenizer.cpp

#include "Tokenizer.h"
#include<istream>
#include<sstream>
#include<algorithm>

// Takes a string and puts it into tokens
bool Tokenizer::lineToTokens(const std::string& line)
{
	// set up our line number
	int lineNum = 0;
	int columnNum = 0;
	if (coordinates_.size() > 0)
	{
		lineNum = coordinates_.back().first + 1;
	}

	std::istringstream iss(line);
	std::string token;

	while (iss)
	{
		iss >> token;

		std::string::const_iterator iter = 
			search(line.begin(), line.end(), token.begin(), token.end());

		if (iter == line.end())
		{
			return false;
		}

		columnNum = std::distance(line.begin(), iter);

		tokens_.push_back(token);
		std::pair<int, int> coord = { lineNum, columnNum };
		coordinates_.push_back(coord);
	}

	if (iss.eof()) return true;
	else return false;
}

// Reads the file in, tokenizing as it goes
bool Tokenizer::readFile(std::istream& istr)
{
	std::string line;

	//while the file is legit, pass each line to lineToTokens
	while (istr)
	{
		std::getline(istr, line);
		lineToTokens(line);
	}

	// if we're done because we reached eof, return true. If something went
	// wrong, return false
	if (istr.eof()) return true;
	else return false;
}

// prints the tokens to the console
void Tokenizer::printTokens(std::ostream& ostr) const
{

}