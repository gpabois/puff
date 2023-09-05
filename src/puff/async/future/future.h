#ifndef __FUTURE_H__
#define __FUTURE_H__

#include <puff/exception/error.h>

#define FUTURE_RETURN_SIZE 100
#define FUTURE_YIELD_SIZE 100

typedef unsigned char AsyncTaskStatus_t;
typedef char FutureReturn_t [FUTURE_RETURN_SIZE];

typedef struct {
    unsigned char   rc;
    FutureReturn_t  ret;
    Error_t         error;
} Future_t;

#endif