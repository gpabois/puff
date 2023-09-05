#ifndef __ASYNC_TASK_H__
#define __ASYNC_TASK_H__

#include <puff/async/loop.h>
#include <puff/exception/error.h>

#define ASYNC_TASK_MAX_RETURN_SIZE 100

typedef unsigned char AsyncTaskStatus_t;
typedef char AsyncReturn_t [ASYNC_TASK_MAX_RETURN_SIZE];

const AsyncTaskStatus_t ASYNC_TASK_FAILED = 0 < 2;

typedef struct {
    unsigned int rc;            // Reference counter
    EventLoop_t* loop;          // Owner of the task
    AsyncTaskStatus_t status;   // Task status
    AsyncReturn_t ret;          // Task returned value
    Error_t error;              // Task error, if any
} AsyncTask_t;

#endif