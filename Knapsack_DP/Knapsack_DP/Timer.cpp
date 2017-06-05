#include "Timer.h"



Timer::Timer()
{
	memset(&pcStart, 0, sizeof(pcStart));
	memset(&pcStop, 0, sizeof(pcStop));
}

void Timer::start()
{
	QueryPerformanceCounter(&pcStart);
	memcpy(&pcStop, &pcStart, sizeof(pcStart));
}

double Timer::stop(Resolution resolution)
{
	QueryPerformanceCounter(&pcStop);
	return getTime();
}

double Timer::getTime(Resolution resolution)
{
	LARGE_INTEGER elapsedMicroseconds, frequency;
	QueryPerformanceFrequency(&frequency);

	elapsedMicroseconds.QuadPart = pcStop.QuadPart - pcStart.QuadPart;
	elapsedMicroseconds.QuadPart *= 1000000;
	elapsedMicroseconds.QuadPart /= frequency.QuadPart;

	return convertResolution(MICROSECONDS, resolution, static_cast<double>(elapsedMicroseconds.QuadPart));
}

double Timer::convertResolution(Resolution from, Resolution to, double time)
{
	return time * static_cast<double>(from / to);
}
