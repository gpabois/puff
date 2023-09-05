#ifndef __ASYNC_FUNC_H__
#define __ASYNC_FUNC_H__

#include <puff/std/setjmp.h>
#include <puff/async/future/future.h>
#include <puff/yarn/yarn.h>

#define CORO_MAX_CALL_STACK_SIZE 1000
#define CORO_MAX_EXCEPTION_STACK_SIZE 100

typedef char AsyncCallStack_t [CORO_MAX_CALL_STACK_SIZE];
typedef char AsyncExceptionStack_t [CORO_MAX_EXCEPTION_STACK_SIZE];

typedef struct {
    Yarn_t yarn; // Store everything related to the execution flow (exception, call stack...)
    
    unsigned char rc; // Reference counter
    AsyncCallStack_t call_stack; // Call stack
    AsyncExceptionStack_t exc_stack; // Exception stack

    Future_t* fut; // The task bound to the async func.

} Coroutine_t;

/*
* Setup the async task context and jump back to the caller
*/
void inline __attribute__((always_inline)) __setup_coro(Coroutine_t* coro, jmp_buf caller);

/*
* Return to event loop from async task.
*/
void ret_from_coro(Coroutine_t* coro);

/**
*  Execute the async task
*/
void next_coro(Coroutine_t* coro);


#endif