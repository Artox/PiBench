// C++ Timer Class
#include "Timer.hpp"

#include <ctime>
using std::clock;

Timer::Timer()
{
	
}

void Timer::start()
{
	t_start = clock();
}

void Timer::stop()
{
	t_end = clock();
}

void Timer::continue_()
{
	t_start = -ticks() + clock();
}

uint32_t Timer::ticks()
{
	return t_end - t_start;
}

uint32_t Timer::seconds()
{
	return ticks() / CLOCKS_PER_SEC;
}

uint32_t Timer::milliseconds()
{
	return ticks() * 1000 / CLOCKS_PER_SEC;
}


// C Library
#include "Timer.h"

void *Timer_create()
{
	Timer *t = new Timer;
	return t;
}

void Timer_start(void *t)
{
	((Timer *)t)->start();
}

void Timer_stop(void *t)
{
	((Timer *)t)->stop();
}

void Timer_continue(void *t)
{
	((Timer *)t)->continue_();
}

uint32_t Timer_seconds(void *t)
{
	return ((Timer *)t)->seconds();
}

uint32_t Timer_milliseconds(void *t)
{
	return ((Timer *)t)->milliseconds();
}

void Timer_delete(void *t)
{
	delete ((Timer *)t);
}
