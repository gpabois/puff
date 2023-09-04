#ifndef __ASYNC_TASK_QUEUE_H__
#define __ASYNC_TASK_QUEUE_H__

#include <puff/async/task/task.h>

typedef struct {
    AsyncTask_t** base;
    unsigned int capacity;
    unsigned int read, write;

} AsyncTaskQueue_t;

void init_async_task_queue(AsyncTaskQueue_t* queue, AsyncTask_t** base, unsigned int capacity) {
    queue->base = base;
    queue->capacity = capacity;
    queue->read = queue->write = 0;
}

#endif