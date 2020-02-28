// Luke Underwood
// 1/23/20
// Lab02
// Timer.h

// Refined for use in Timer.lib

#include "pch.h"
#include "framework.h"
#include "Timer.h"
#include<iostream>

Timer::Timer() : duration_(0)
{
	startTimepoint_ = system_clock::now();
}

Timer::Timer(const Timer& old) : duration_(0)
{
	*this = old;
}

Timer::Timer(time_point<system_clock> start) : duration_(0)
{
	startTimepoint_ = start;
}

Timer::~Timer() {}

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
