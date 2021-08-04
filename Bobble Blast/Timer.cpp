#include "Timer.h"
#include <SDL.h>

Timer* Timer::Instance = nullptr;

float Timer::Tick()
{
	TimeElapsed = (float)(LastFrame - FirstFrame) / SDL_GetPerformanceFrequency();

	TimeElapsed *= 1000; //milliseconds

	return TimeElapsed;
}

void Timer::Start()
{
    FirstFrame = SDL_GetPerformanceCounter();
}

void Timer::End()
{
	LastFrame = SDL_GetPerformanceCounter();
}

void Timer::Reset()
{
	FirstFrame = 0.0f;
	LastFrame = 0.0f;
}
