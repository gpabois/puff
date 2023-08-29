#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <setjmp.h> 

#define EXCEPTION_ERROR_MAX_SIZE 1000;
#define EXCEPTION_STACK_SIZE 100;

static Exception_t exc_stack[EXCEPTION_STACK_SIZE];
static Exception_t exc_tos = 0;

/*
* Exception context
*/
typedef struct {
    jmp_buf env;
    char error[EXCEPTION_ERROR_MAX_SIZE];
} Exception_t;

/**
 * Push an exception block.
*/
int Exception_push() {
    if(exc_tos == 0) 
        exc_tos = &exc_stack[0];
    else 
        exc_tos++;
}

int Exception_try() {
    return setjmp(exc_tos->env)
}

Exception_t* Exception_current() {
    return exc_tos;
}

/**
 * Pop an exception block.
*/
int Exception_pop() {
    if(exc_tos == &exc_stack[0]) 
        exc_tos = 0;
    else
        exc_tos--;
}

#define begin_exception Exception_push();
#define try if(!Exception_try()) {
#define catch(type, varname) } else {\
    type varname = *(type*)Exception_current()->error;
}
#define end_exception Exception_pop();
#endif