#pragma once
#include <Windows.h>
#include <cmath>

enum Resolution
{
	MICROSECONDS,
	MILISECONDS,
	SECONDS
};

class Timer
{
public:
	Timer();

	void start();
	double stop(Resolution resolution = SECONDS);
	double getTime(Resolution resolution = SECONDS);

private:
	LARGE_INTEGER pcStart;
	LARGE_INTEGER pcStop;
};

