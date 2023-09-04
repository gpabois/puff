#ifndef __ERROR_H__
#define __ERROR_H__

#define EXCEPTION_ERROR_MAX_SIZE 1000

#include <puff/std/string.h>

// Error_t receiver, size is 1 Ko.
typedef char Error_t[EXCEPTION_ERROR_MAX_SIZE];

// Copy the error
void copy_error(Error_t* dest, Error_t* src) {
    memcpy(dest, src, EXCEPTION_ERROR_MAX_SIZE);
}

#endif