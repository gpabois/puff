#ifndef __ASYNC_TASK_ALLOC_H__
#define __ASYNC_TASK_ALLOC_H__

#include <puff/async/task/task.h>

#define ASYNC_TASK_MAX_SIZE 512

/* Alloc a new async task. Returns 0 if failed. */
char alloc_async_task(AsyncTask_t**dest);

#endif