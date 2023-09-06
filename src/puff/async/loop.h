#ifndef __LOOP_H__
#define __LOOP_H__

#include <puff/async/timer/queue.h>
#include <puff/async/coro/queue.h>

#define ERR_TIMER_OVERFLOW 1
#define ERR_CORO_OVERFLOW 2

typedef struct {
    AsyncTimerQueue_t timers;
    CoroQueue_t ready;
} EventLoop_t;

// Get the current loop
// Throws an error if there are no loop.
EventLoop_t* get_current_loop();

// Step the loop
void step_loop(EventLoop_t* loop);

#endif