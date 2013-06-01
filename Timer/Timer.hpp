#ifndef HAVE_TIMER_HPP
#define HAVE_TIMER_HPP

#include <ctime>
using std::clock_t;
#include <cstdint>
using std::uint32_t;

class Timer
{
private:
	// number of elapsed ticks at timer start and end
	clock_t t_start;
	clock_t t_end;
public:
	Timer();
	void start();
	void stop();
	uint32_t ticks();
	uint32_t seconds();
	uint32_t milliseconds();
};

#endif
