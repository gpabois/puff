#ifndef __ASYNC_TASK_H__
#define __ASYNC_TASK_H__

#include "puff/abi/setjmp.h"

#define ASYNC_TASK_MAX_RETURN_SIZE 100
#define ASYNC_TASK_MAX_STACK_SIZE 1000

typedef struct {
    jmp_buf env;
    unsigned char rc;
    char stack[ASYNC_TASK_MAX_STACK_SIZE];
    char ret[ASYNC_TASK_MAX_RETURN_SIZE];
} AsyncTask_t;

/*
* [PRIVATE] Acquire the task, avoid being freed.
*/
void AsyncTask_acquire(AsyncTask_t* task);

/*
* [PRIVATE] Release the task, allow to be freed.
*/
void AsyncTask_release(AsyncTask_t* task);



#endif