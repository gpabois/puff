#ifndef __ASYNC_TASK_ALLOC_H__
#define __ASYNC_TASK_ALLOC_H__

#include <puff/async/task/task.h>

#define ASYNC_TASK_MAX_SIZE 1000

char AsyncTask_alloc(AsyncTask_t**dest);

#endif