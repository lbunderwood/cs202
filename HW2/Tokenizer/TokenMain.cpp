// Luke Underwood
// 2/10/2020
// cs202
// HW2
// Tokenizer
// TokenMain.cpp

#include<iostream>
#include<fstream>
#include<algorithm>

#include"Tokenizer.h"
#include"Timer.h"

// print a message to inform the user that their command line arguments need
// to be in another format
void argumentError()
{
	std::cout << "ERROR: BAD ARGUMENTS" << std::endl
		<< "Please enter the filename, then optionally the --lineonly "
		<< "argument will read in the file, without printing the results.";
}

int main(int argc, char** argv)
{
	Timer timer;

	// initialize vairbles so they don
	std::string filename;
	bool lineonly = false;

	// make sure the number of args is correct
	if (argc < 2 || argc > 3)
	{
		argumentError();
		return 0;
	}
	else
	{
		// make sure argument 1 is a filename
		std::string check = argv[1];
		check = check.substr(check.size() - 4, check.size() - 1);
		if (check == ".txt")
		{
			filename = argv[1];
		}
		else
		{
			argumentError();
			return 0;
		}

		// check for --lineonly
		if (argc == 3)
		{
			if (argv[2] == "--lineonly")
			{
				lineonly = true;
			}
			else
			{
				argumentError();
				return 0;
			}
		}
	}

	std::ifstream ifs(filename);

	Tokenizer tokenizer;
	tokenizer.readFile(ifs);

	if (lineonly)
	{
		tokenizer.printTokens(std::cout);
	}

	timer.end();
	std::cout << "\n\n\nTime Elapsed: " << timer.getDuration() << " s";
}