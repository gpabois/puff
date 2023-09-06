#ifndef __ERROR_H__
#define __ERROR_H__

#include <puff/std/stdarg.h>

#define ERROR_MAX_SIZE 1000

// Error_t receiver, size is 1 Ko.
typedef struct {
    int code;
    char msg[ERROR_MAX_SIZE];
} Error_t;

// Copy the error
void vsprintf_error(Error_t* dest, const char* fmt, va_list list);
void copy_error(Error_t* dest, const Error_t* src);

#endif