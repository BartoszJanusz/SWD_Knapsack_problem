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

	double retVal = (double)elapsedMicroseconds.QuadPart;
	switch (resolution)
	{
		case MICROSECONDS:
			break;
		case MILISECONDS:
			retVal /= 1000;
			break;
		case SECONDS:
			retVal /= 1000000;
			break;
		default:
			// Should not be here
			retVal = nan("");
			break;
	}

	return retVal;
}