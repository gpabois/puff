#ifndef __LOOP_H__
#define __LOOP_H__

#include <puff/async/timer/queue.h>
#include <puff/async/coro/queue.h>

#define EVENT_LOOP_TIMER_LEN 100
#define EVENT_LOOP_READY_LEN 100

#define ERR_TIMER_OVERFLOW 1
#define ERR_CORO_OVERFLOW 2

/**
 * @brief Event loop
 */
typedef struct {
    AsyncTimerQueue_t timers;
    CoroQueue_t ready;

    AsyncTimer_t* __timers[EVENT_LOOP_TIMER_LEN];
    Coro_t* __ready[EVENT_LOOP_READY_LEN];
} EventLoop_t;

/**
 * @brief Initialise an event loop
 * 
 * @param loop 
 */
void init_loop(EventLoop_t* loop);

/**
 * @brief Execute the loop for one step.
 * 
 * @param loop 
 */
void step_loop(EventLoop_t* loop);

#endif