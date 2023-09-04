#ifndef __ASYNC_FUNC_H__
#define __ASYNC_FUNC_H__

#include <puff/std/setjmp.h>
#include <puff/async/loop.h>
#include <puff/yarn/yarn.h>


#define ASYNC_TASK_MAX_CALL_STACK_SIZE 1000
#define ASYNC_TASK_MAX_EXCEPTION_STACK_SIZE 100

typedef char AsyncCallStack_t [ASYNC_TASK_MAX_CALL_STACK_SIZE];
typedef char AsyncExceptionStack_t [ASYNC_TASK_MAX_EXCEPTION_STACK_SIZE];

typedef struct {
    Yarn_t yarn;                        // Store everything related to the execution flow (exception, call stack...)
    
    unsigned char rc;                   // Reference counter
    AsyncCallStack_t call_stack;        // Call stack
    AsyncExceptionStack_t exc_stack;    // Exception stack

    AsyncTask_t*    task;               // The task bound to the async func.
} AsyncFunc_t;

/*
* Setup the async task context and jump back to the caller
*/
void inline __attribute__((always_inline)) __setup_async_func(AsyncFunc_t* task, jmp_buf caller);

/*
* Return to event loop from async task.
*/
void ret_from_async_task();

/**
*  Execute the async task
*/
void exec_async_fun(AsyncFunc_t* task);

/*
* Acquire the task, avoid being freed.
*/
void __acquire_async_task(AsyncTask_t* task);

/*
* Release the task, allow to be freed.
*/
void __release_async_task(AsyncTask_t* task);



#endif