#include <puff/async/timer/queue.h>

void init_async_timer_queue(AsyncTimerQueue_t* queue) {
    queue->read = queue->write = 0;
}

LockedAsyncTimerQueue_t lock_async_timer_queue(AsyncTimerQueue_t* queue) {
    LockedAsyncTimerQueue_t lock = {
        .queue = queue,
        .limit = queue->write
    };

    return lock;
}
