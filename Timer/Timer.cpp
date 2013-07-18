// C++ Timer Class
#include "Timer.hpp"

#include <sys/time.h>

Timer::Timer()
{
	start();
	t_end = t_start;
}

void Timer::start()
{
	gettimeofday(&t_start, 0);
}

void Timer::stop()
{
	gettimeofday(&t_end, 0);
}

/*void Timer::continue_()
{
	t_start = -ticks() + clock();
}*/

/*uint32_t Timer::ticks()
{
	return t_end - t_start;
}*/

uint32_t Timer::seconds()
{
	return t_end.tv_sec - t_start.tv_sec;
}

uint32_t Timer::milliseconds()
{
	return (t_end.tv_sec - t_start.tv_sec)*1000 + (t_end.tv_usec - t_start.tv_usec)/1000;
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

/*void Timer_continue(void *t)
{
	((Timer *)t)->continue_();
}*/

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
