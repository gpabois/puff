#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <puff/std/setjmp.h>
#include <puff/error.h>

#define __auto_typeof(x) __typeof__(({__auto_type y=x; y;}))

/*
* An exception try/catch block
*/
typedef struct {
    jmp_buf caller;
    Error_t error;
} Exception_t;

char __try_exception();
void __clear_exception();

void throw(int code, const char* fmt, ...);
void throw_err(Error_t* err);

Exception_t* __current_exception();

// try {} catch(Error_t error) {} finally
#define try if(!__try_exception()) {
#define catch(lvalue) } else {\
    Exception_t* curr = __current_exception();\
    if(curr == 0) panic("no exception block exist."); \
    Error_t lvalue = __current_exception()->error;
#define finally } __clear_exception();
#endif