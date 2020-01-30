//Luke Underwood
//1/28/2020
//cs202
//Lab03
//Main.cpp

#include<iostream>

#include"Timer.h"

int main()
{
	std::cout << "Making raw pointer" << std::endl;
	Timer* tPtr = new Timer;

	time_point<system_clock> time = system_clock::now();

	std::cout << "Making unique pointer" << std::endl;
	auto uPtr1 = std::make_unique<Timer>(time);
	{
		std::cout << "Transferring ownership of unique pointer" << std::endl;
		auto uPtr2 = std::move(uPtr1);
	}

	{
		std::cout << "Making shared pointer" << std::endl;
		auto sPtr1 = std::make_shared<Timer>(time);

		{
			std::cout << "Creating a second shared pointer to the same object"
				<< std::endl;
			auto sPtr2 = sPtr1;
		}
	}
}