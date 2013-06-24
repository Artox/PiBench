#ifndef HAVE_TIMER_HPP
#define HAVE_TIMER_HPP

#include <sys/time.h>
#include <cstdint>
using std::uint32_t;

class Timer
{
private:
	// number of elapsed ticks at timer start and end
	struct timeval t_start;
	struct timeval t_end;
public:
	Timer();
	void start();
	void stop();
	//void continue_();
	//uint32_t ticks();
	uint32_t seconds();
	uint32_t milliseconds();
};

#endif
