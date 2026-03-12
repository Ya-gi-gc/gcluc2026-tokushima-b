#include "Timer.h"
#include "DebugPrint.h"

time_t Timer::startTime;

void Timer::Start()
{
	startTime = time(NULL);
}

void Timer::Update()
{
	int elapsed = (int)(time(NULL) - startTime);
	//int remain = 180 - elapsed;
	int min = elapsed / 60;
	int sec = elapsed % 60;

		DebugPrint::Print("TIME %d:%02d", min, sec); 
}