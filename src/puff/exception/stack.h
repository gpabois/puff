#ifndef __EXCEPTION_CONTEXT_H__
#define __EXCEPTION_CONTEXT_H__

#include <puff/exception/exception.h>
#include <puff/cpu/cpu.h>


#define DEFAULT_EXCEPTION_STACK_SIZE 100
#define _EXC_CAPACITY_TYPE unsigned int

/**
 * Exception context
*/
typedef struct {
    Exception_t* base;
    Exception_t* tos;
    _EXC_CAPACITY_TYPE size;
} ExceptionStack_t;

// Initialise the exception system.
// Must be called at the start of the firmware execution.
void __init_exception_sys();

// Initialise an exception context.
void init_exception_stack(ExceptionStack_t* stack, Exception_t* base, _EXC_CAPACITY_TYPE capacity);

// Set a new exception context
void set_exception_stack(ExceptionStack_t* ctx);

// Restore the previous exception context.
ExceptionStack_t* restore_exception_context();

// Return the current exception context.
ExceptionStack_t* __get_current_exception_stack();

#endif