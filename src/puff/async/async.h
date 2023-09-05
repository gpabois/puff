#ifndef __ASYNC_H__
#define __ASYNC_H__

#include <puff/async/task/alloc.h>
#include <puff/async/func/func.h>
#include <puff/func/stack.h">

#define async AsyncFunc_t* 

/**
* Parameters has to be declared as "type(varname)"
* Hack: https://stackoverflow.com/a/44759398), with -O0 flag, the copy is ignored by the compiler.
*/
#define async_def(return_t, name, ...) AsyncTask_t* name(__VA_ARGS__) {\
    AsyncTaskRef_t task;\
    jmp_buf caller;\
\
    if(!alloc_async_task(&task))\
        return 0;\
\
    if(!setjmp(caller)) { \
        __run_##name(task, caller, __VA_ARGS__); \
    } \
\
    return task;\
}\
\
static void __run_##name(AsyncTask_t* task, jmp_buf caller, __VA_ARGS__) {\
    init_async_task(task, caller);\
    _Generic(typeof(return_t)*{0},\
        void*: __##name(task, a);,\
        default: if (sizeof(return_t) < ASYNC_TASK_MAX_RETURN_SIZE) {\
            *(*return_t)task->ret = __##name(task, a); \
        }\
    )\
}\
static return_t __##name(AsyncTask_t* task, __VA_ARGS__) 

#endif