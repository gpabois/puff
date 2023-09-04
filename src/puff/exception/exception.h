#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <puff/std/setjmp.h>
#include <puff/cpu/cpu.h>
#include <puff/exception/error.h>

#define __auto_typeof(x) __typeof__(({__auto_type y=x; y;}))

/*
* An exception try/catch block
*/
typedef struct {
    jmp_buf caller;
    Error_t error;
} Exception_t;

char try_exception();
void throw_exception();

// Pop the current exception block, panics if there is an underflow.
void clear_exception();

Exception_t* current_exception();

#define try if(!try_exception()) {
#define catch(type, varname) } else {\
    type varname = *(type*)current_exception()->error;\
} clear_exception();
#define throw(err_expr) {\
    Exception_t* exc = current_exception();\
    __auto_typeof(err_expr)* err = (__auto_typeof(err_expr))exc->error;\
    *err = err_expr;\
    throw_exception();\
}
#endif