// Luke Underwood
// 2/10/2020
// cs202
// HW2
// Tokenizer
// Tokenizer.h

#include<vector>
#include<string>

class Tokenizer
{
public:

	// Default Constructor
	Tokenizer() {}

	// Takes a string and puts it into tokens
	bool lineToTokens(const std::string& line);

	// Reads the file in, tokenizing as it goes
	bool readFile(std::istream& instr);

	// prints the tokens to the console
	void printTokens(std::ostream& ostr) const;

private:

	//stores tokens
	std::vector<std::string> tokens_;

	// stores coordinate positions of each token with corresponding index
	// as line, column
	std::vector<std::pair<int, int>> coordinates_;
};

