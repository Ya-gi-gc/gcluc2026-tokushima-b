#include "Timer.h"
#include "DebugPrint.h"

time_t Timer::startTime;
int Timer::resultTime = 0;
bool Timer::isRunning = false;

void Timer::Start()
{
	startTime = time(NULL);
	isRunning = true;
}

void Timer::Stop()
{
    resultTime = (int)(time(NULL) - startTime);
    isRunning = false;
}

void Timer::Update()
{
    if (!isRunning) return;

    int elapsed = (int)(time(NULL) - startTime);
    int min = elapsed / 60;
    int sec = elapsed % 60;

    resultTime = elapsed;

    DebugPrint::Print("TIME %d:%02d", min, sec);
}

void Timer::DebugPrintTime()
{
    int elapsed = resultTime;
    int min = elapsed / 60;
    int sec = elapsed % 60;

    DebugPrint::Print("TIME %d:%02d", min, sec);
}