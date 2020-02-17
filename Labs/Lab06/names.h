#ifndef NAMES_H
#define NAMES_H

#include<string>

namespace name
{
	class Names
	{
	public:
		Names();

		void printNames();

	private:

		std::string name1_;
		std::string name2_;
		std::string name3_;
	};

	void foo();

}

#endif NAMES_H