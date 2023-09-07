#ifndef __ASYNC_COMMAND_H__
#define __ASYNC_COMMAND_H__

#include <puff/async/timer.h>

#define AsyncTimerCmd 1
#define AsyncCallSoonCmd 2

/**
 * @brief An async command
 * 
 * @note
 * An async command is yielded by a coroutine to 
 * drive the event loop.  
 */
typedef struct {
    unsigned char type;
    union {
        AsyncTimer_t* timer;
    } arg;
} AsyncCommand_t;

/**
 * @brief Returns an async command for the event loop.
 * 
 * @param timer 
 * @return AsyncCommand_t 
 */
AsyncCommand_t async_timer(AsyncTimer_t* timer) {
    AsyncCommand_t cmd  = {
        .type = AsyncTimerCmd,
        .arg.timer = timer
    };
    return cmd;
}

#endif