#ifndef HAVE_TIMER_H
#define HAVE_TIMER_H

#ifdef __cplusplus
#include <cstdint>
using std::uint32_t;
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void *Timer_create();
void Timer_start(void *t);
void Timer_stop(void *t);
//void Timer_continue(void *t);
uint32_t Timer_seconds(void *t);
uint32_t Timer_milliseconds(void *t);
void Timer_delete(void *t);

#ifdef __cplusplus
}
#endif

#endif
