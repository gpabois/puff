#ifndef __TIMER_H__
#define __TIMER_H__

#include <puff/async/macro.h>
#include <puff/std/time.h>

typedef struct {
    clock_t t;
    Coro_t* coro;
} AsyncTimer_t;

// Async sleep for n ms.
async(void) async_sleep(int ms);

#endif