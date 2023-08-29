#ifndef __ASYNC_TASK_ALLOC_H__
#define __ASYNC_TASK_ALLOC_H__

#include "./task.h"

#define ASYNC_TASK_MAX_SIZE 1000

static AsyncTask_t Heap[ASYNC_TASK_MAX_SIZE];

char AsyncTask_alloc(AsyncTask_t**dest);

#endif