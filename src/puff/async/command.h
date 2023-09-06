#ifndef __ASYNC_COMMAND_H__
#define __ASYNC_COMMAND_H__

#include <puff/async/timer.h>

typedef struct {
    unsigned char type;
    union {
        AsyncTimer_t* timer;
    } arg;
} AsyncCommand_t;

#define AsyncTimerCmd 1
#define AsyncCallSoonCmd 2

AsyncCommand_t async_timer(AsyncTimer_t* timer) {
    AsyncCommand_t cmd  = {
        .type = AsyncTimerCmd,
        .arg.timer = timer
    };
    return cmd;
}

#endif