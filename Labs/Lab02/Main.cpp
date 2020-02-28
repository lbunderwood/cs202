// Luke Underwood
// 1/23/20
// Lab02
// Main.cpp

#include<iostream>
#include<vector>
#include<string>

#include"Timer.h"

#pragma comment(lib, "Timer.lib")

int main()
{
	std::vector<Timer> timers;
	std::string placeholder;
	time_point<system_clock> programStart = system_clock::now();

	for (int i = 0; i < 5; i++)
	{
		Timer time;
		std::cout << "Press ENTER to start the timer\n";
		std::getline(std::cin, placeholder);
		time.start();

		std::cout << "Press ENTER to stop the timer\n";
		std::getline(std::cin, placeholder);
		time.end();

		timers.push_back(time);
	}

	std::vector<Timer> timercopies;
	for (auto n : timers)
	{
		timercopies.push_back(n);
		std::cout << n.getDuration() << std::endl;
	}
	for (auto n : timercopies)
	{
		std::cout << n.getDuration() << std::endl;
	}

	Timer totalTime(programStart);
	totalTime.end();
	std::cout << "Total time elapsed: " << totalTime.getDuration();
}