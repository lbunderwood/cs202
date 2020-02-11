// Luke Underwood
// 1/23/20
// Lab02
// Timer.h

#ifndef TIMER_H
#define TIMER_H

#include<chrono>
using namespace std::chrono;

class Timer
{
public:
	Timer();

	Timer(const Timer& old);

	Timer(time_point<system_clock> start);

	~Timer() {}

	void start();

	void end();

	double getDuration();

private:
	
	double duration_;

	time_point<system_clock> startTimepoint_;
	time_point<system_clock> endTimepoint_;

};

#endif