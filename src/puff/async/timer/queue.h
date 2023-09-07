#ifndef __ASYNC_TIMER_QUEUE_H__
#define __ASYNC_TIMER_QUEUE_H__

#include <puff/async/timer.h>
#include <puff/std/stddef.h>

/**
 * @brief A queue for timer references. 
 */
typedef struct {
    AsyncTimer_t** base;
    size_t capacity;
    size_t read;
    size_t write;
} AsyncTimerQueue_t;

/**
 * @brief A locked-queue that pops until the limit.
 * @note 
 * This allow to enqueue new element, while dequeuing.
 */
typedef struct {
    AsyncTimerQueue_t* queue;
    size_t limit;
} LockedAsyncTimerQueue_t;

/**
 * @brief Initialise a timer queue
 * 
 * @param queue 
 * @param base a pointer to an array of references
 * @param capacity the capacity of the array
 */
void init_async_timer_queue(AsyncTimerQueue_t* queue, AsyncTimer_t** base, size_t capacity);

/**
 * @brief Dequeue a reference to a timer
 * 
 * @param queue 
 * @param dest the receiver of the timer reference
 * @return char >0 if there is a timer to pop, 0 else.
 */
char dequeue_async_timer_queue(AsyncTimerQueue_t* queue, AsyncTimer_t** dest);
char enqueue_async_timer_queue(LockedAsyncTimerQueue_t* queue, AsyncTimer_t* timer);

LockedAsyncTimerQueue_t lock_async_timer_queue(AsyncTimerQueue_t* queue);
char dequeue_locked_async_timer_queue(LockedAsyncTimerQueue_t* lock, AsyncTimer_t** dest);

#endif