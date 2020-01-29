//Luke Underwood
//1/28/2020
//cs202
//Lab03
//Main.cpp

#include<iostream>

#include"Timer.h"

int main()
{
	Timer* tPtr = new Timer;

	time_point<system_clock> time = system_clock::now();

	auto uPtr1 = std::make_unique<Timer>(time);

	auto uPtr2 = std::move(uPtr1);

	(*uPtr2).end();

	auto sPtr1 = std::make_shared<Timer>;

	delete tPtr;
}