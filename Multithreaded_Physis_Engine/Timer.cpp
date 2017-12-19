#include "stdafx.h"
#include "Timer.h"

/**************************************************************************
* Function: Constructor
**************************************************************************/
Timer::Timer()
{
	startTime = -1;
	currentTime = -1;
}

/**************************************************************************
* Function: Deconstructor
**************************************************************************/
Timer::~Timer()
{
}

/**************************************************************************
* Function: HasTimeElapsed
* Returns true if the time in miliseconds has elapsed.
**************************************************************************/
bool Timer::hasTimeElapsed(const int & miliseconds)
{
	return currentTime - startTime >= miliseconds;
}

/**************************************************************************
* Function: Reset Timer
* Definition: Clears the timer.
**************************************************************************/
void Timer::resetTimer()
{
	startTime = -1;
	currentTime = -1;
}

/**************************************************************************
* Function: Update Timer
* Definition: Sets the current time to the argument passed in.
**************************************************************************/
void Timer::updateTimer(const int & miliseconds)
{
	currentTime = miliseconds;
}

/**************************************************************************
* Function: Start timer
* Definition: Starts the timer
**************************************************************************/
void Timer::startTimer(const int & miliseconds)
{
	startTime = miliseconds;
	currentTime = miliseconds;
}
