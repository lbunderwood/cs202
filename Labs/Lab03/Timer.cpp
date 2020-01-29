// Luke Underwood
// 1/23/20
// Lab02
// Timer.cpp

#include "Timer.h"
#include<iostream>

Timer::Timer() : duration_(0) 
{ 
	startTimepoint_ = system_clock::now();
	std::cout << "Timer Created (default)!" << std::endl; 
}

Timer::Timer(const Timer& old) : duration_(0)
{
	*this = old;
	std::cout << "Timer Created (copy)!" << std::endl;
}

Timer::Timer(time_point<system_clock> start) : duration_(0)
{
	startTimepoint_ = start;
	std::cout << "Timer Created (passed a start time)!" << std::endl;
}

Timer::~Timer() 
{
	std::cout << "Timer Deleted" << std::endl;
}

void Timer::start()
{
	startTimepoint_ = system_clock::now();
}

void Timer::end()
{
	endTimepoint_ = system_clock::now();
	auto difference = endTimepoint_ - startTimepoint_;
	duration_ = duration<double, std::milli>(difference).count();
	duration_ /= 1000;
}

double Timer::getDuration()
{
	return duration_;
}
