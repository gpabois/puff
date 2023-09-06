#ifndef __ASYNC_CORO_QUEUE_H__
#define __ASYNC_CORO_QUEUE_H__

#include <puff/async/coro.h>

#define ASYNC_CORO_MAX_CAPACITY 100
#define ASYNC_CORO_INDEX_TYPE unsigned char

typedef struct {
    Coro_t* base[ASYNC_CORO_MAX_CAPACITY];
    ASYNC_CORO_INDEX_TYPE read;
    ASYNC_CORO_INDEX_TYPE write;
} CoroQueue_t;

// A locked-queue that pops until the limit.
// This allow to enqueue new element, while dequeuing.
typedef struct {
    CoroQueue_t* queue;
    ASYNC_CORO_INDEX_TYPE limit;
} LockedCoroQueue_t;

void init_coro_queue(CoroQueue_t* queue);
char dequeue_coro_queue(CoroQueue_t* queue, Coro_t** dest);
char enqueue_coro_queue(CoroQueue_t* queue, Coro_t* coro);

LockedCoroQueue_t lock_coro_queue(CoroQueue_t* queue);
char dequeue_locked_coro_queue(LockedCoroQueue_t* lock, Coro_t** dest);
char enqueue_locked_coro_queue(LockedCoroQueue_t* lock, Coro_t* coro);

#endif