#ifndef __EXCEPTION_SYS_H__
#define __EXCEPTION_SYS_H__

#include <puff/exception/context.h>
#include <puff/cpu/cpu.h>

#define DEFAULT_EXCEPTION_STACK_SIZE 100

// Initialise the exception system.
// Must be called at the start of the firmware execution.
void __init_exception_sys();

// Set a new exception context
void set_exception_context(ExceptionContext_t* ctx);

// Restore the previous exception context.
ExceptionContext_t* restore_exception_context();

// Return the current exception context.
ExceptionContext_t* __get_current_exception_context();

#endif