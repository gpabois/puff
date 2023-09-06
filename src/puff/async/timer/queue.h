#ifndef __ASYNC_TIMER_QUEUE_H__
#define __ASYNC_TIMER_QUEUE_H__

#include <puff/async/timer.h>

#define ASYNC_TIMER_MAX_CAPACITY 100
#define ASYNC_TIMER_INDEX_TYPE unsigned char

typedef struct {
    AsyncTimer_t* base[ASYNC_TIMER_MAX_CAPACITY];
    ASYNC_TIMER_INDEX_TYPE read;
    ASYNC_TIMER_INDEX_TYPE write;
} AsyncTimerQueue_t;

// A locked-queue that pops until the limit.
// This allow to enqueue new element, while dequeuing.
typedef struct {
    AsyncTimerQueue_t* queue;
    ASYNC_TIMER_INDEX_TYPE limit;
} LockedAsyncTimerQueue_t;

void init_async_timer_queue(AsyncTimerQueue_t* queue);
char dequeue_async_timer_queue(AsyncTimerQueue_t* queue, AsyncTimer_t** dest);
char enqueue_async_timer_queue(LockedAsyncTimerQueue_t* queue, AsyncTimer_t* timer);

LockedAsyncTimerQueue_t lock_async_timer_queue(AsyncTimerQueue_t* queue);
char dequeue_locked_async_timer_queue(LockedAsyncTimerQueue_t* lock, AsyncTimer_t** dest);
char enqueue_locked_async_timer_queue(LockedAsyncTimerQueue_t* lock, AsyncTimer_t* timer);

#endif