#ifndef __TIMER_H__
#define __TIMER_H__

#include <puff/async/macro.h>
#include <puff/std/time.h>

typedef struct {
    clock_t t;
    Coro_t* coro;
} AsyncTimer_t;

/**
 * @brief Sleep for n ms.
 * 
 * @param ms The number of miliseconds to sleep.
 */
async(void) async_sleep(int ms);

/**
 * @brief Zero-overhead sleep
 * 
 * @note
 * It does not allocate a new generator. 
 */
#define await_sleep(ms) {\
    AsyncTimer_t timer = {\
        .coro = current_coro,\
        .t = clock() + ms * 1000 / CLOCKS_PER_SEC\
    };\
    yield(async_timer(&timer));\
}

#endif