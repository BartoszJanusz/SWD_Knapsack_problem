#pragma once
#include <Windows.h>
#include <cmath>

enum Resolution
{
	MICROSECONDS = 1,
	MILLISECONDS = MICROSECONDS * 1000,
	SECONDS = MILLISECONDS * 1000
};

class Timer
{
public:
	Timer();

	void start();
	double stop(Resolution resolution = SECONDS);
	double getTime(Resolution resolution = SECONDS);

	static double convertResolution(Resolution from, Resolution to, double time);
private:
	LARGE_INTEGER pcStart;
	LARGE_INTEGER pcStop;
};

