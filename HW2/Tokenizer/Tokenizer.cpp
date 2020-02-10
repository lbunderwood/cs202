// Luke Underwood
// 2/10/2020
// cs202
// HW2
// Tokenizer
// Tokenizer.cpp

#include "Tokenizer.h"
#include<istream>

// Takes a string and puts it into tokens
bool Tokenizer::lineToTokens(const std::string& line)
{

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