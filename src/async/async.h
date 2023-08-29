#ifndef __ASYNC_H__
#define __ASYNC_H__

#include "./task/alloc.h"
#include "puff/abi/stack.h"

#define __type_is_void(expr) _Generic((typeof(expr)*){0}, void*:1, default:0)

#define async AsyncTask_t* 

/**
* Parameters has to be declared as "type(varname)"
* Hack: https://stackoverflow.com/a/44759398), with -O0 flag, the copy is ignored by the compiler.
*/
#define async_def(return_t, name, ...) AsyncTask_t* name(__VA_ARGS__) {\
    AsyncTask_t* task;\
    jmp_buf boot;\
\
    if(!AsyncTask_alloc(&task))\
        return 0;\
\
    if(!setjmp(boot)) { \
        __run_##name(task, boot, __VA_ARGS__); \
    } \
\
    return task;\
}\
\
static void __run_##name(AsyncTask_t* task, jmp_buf boot, __VA_ARGS__) {\
    switch_stack(task->stack, ASYNC_TASK_MAX_STACK_SIZE);\
\
    if(!setjmp(task->env)) { \
        longjmp(boot, 1); \
    }\
\
    _Generic(typeof(return_t)*){0},\
        void*: __##name(task, a);,\
        default: if (sizeof(return_t) < ASYNC_TASK_MAX_RETURN_SIZE) {\
            *(*return_t)task->ret = __##name(task, a); \
        }\
    )\
}\
static return_t __##name(AsyncTask_t* task, __VA_ARGS__) 

async_def(void, foo, int(a)){

}

/* Example
    async asyncFooFunc(int a);

    async_decl(asyncFooFunc, int(a)) {
        //...
    }

    AsyncTask_t* asyncFooFunc(int a) {
        AsyncTask_t* task;
        jmp_buf boot;

        if(!AsyncTask_alloc(&task)) 
            return 0;
        
        if(!setjmp(boot)) {
            __asyncFooFunc(task, a);
        }

        return task;
    }

    static void __enter_asyncFooFunc(AsyncTask_t* task, jmp_buf boot, int a) {
        if(!setjmp(task->env)) {
            longjmp(boot, 1);
        }
        __asyncFooFunc(task, a);
    }

    static void __asyncFooFunc(AsyncTask_t* task, int a) {
        // Expresssion
    }
*/

AsyncTask_t * foo(int(a)) {
  AsyncTask_t * task;
  jmp_buf boot;
  if (!AsyncTask_alloc( & task)) return 0;
  if (!setjmp(boot)) {
    __run_foo(task, boot, int(a));
  }
  return task;
}
static void __run_foo(AsyncTask_t * task, jmp_buf boot, int(a)) {
  switch_stack(task -> stack, 1000);
  if (!setjmp(task -> env)) {
    longjmp(boot, 1);
  }
  _Generic(typeof (void*{0})  ) {
    0
  }, void *: __foo(task, a);,
  default: if (sizeof(void) < 100) {
    *( * void) task -> ret = __foo(task, a);
  })
}
static void __foo(AsyncTask_t * task, int(a));

#endif