#ifndef __EXCEPTION_CONTEXT_H__
#define __EXCEPTION_CONTEXT_H__

#include <puff/exception/exception.h>

#define _EXC_CAPACITY_TYPE unsigned int

/**
* @brief Exception context
*/
typedef struct {
    Exception_t* base;
    Exception_t* tos;
    _EXC_CAPACITY_TYPE size;
} ExceptionContext_t;


// Initialise an exception context.
void init_exception_context(ExceptionContext_t* ctx, Exception_t* base, _EXC_CAPACITY_TYPE capacity);

#endif