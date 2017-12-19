#pragma once
#ifndef TIMER_H
#define TIMER_H

class Timer
{

private:
	int startTime;
	int currentTime;

public:
	Timer();
	~Timer();
	bool hasTimeElapsed(const int & miliseconds);
	void resetTimer();
	void updateTimer(const int & miliseconds);
	void startTimer(const int & miliseconds);
	int timeElapsed() { return currentTime - startTime; }

};

#endif