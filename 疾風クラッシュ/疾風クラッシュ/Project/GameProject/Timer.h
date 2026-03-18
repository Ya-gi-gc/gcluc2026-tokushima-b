#pragma once
#include <time.h>

class Timer
{
private:
	static time_t startTime;
	static int resultTime;
	static bool isRunning;


public:
	static void Start();
	static void Update();
	static void Stop();
	static void DebugPrintTime();
};