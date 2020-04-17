// Lab 13

#include<iostream>
#include<string>

#include"Header.h"

int main()
{
	Wrapper<int> w{ 2 };
	Wrapper<std::string>  s{ "Hello world!" };

	std::cout << w << " " << s << std::endl;
}