#ifndef __LOOP_H__
#define __LOOP_H__

#include <puff/async/timer.h>

typedef struct {

} EventLoop_t;

// Get the current loop
// Throws an error if there are no loop.
EventLoop_t* get_current_loop();

// Add a timer to the loop
// Throws an error if the list is full;
void register_timer(EventLoop_t* loop, AsyncTimer_t* timer);

#endif