#ifndef __YARN_H__
#define __YARN_H__

#include <puff/exception/exception.h>

/**
 * A yarn is a tool to switch between execution flows, handle call, exception stacks.
*/
typedef struct {
    jmp_buf ctx;

    Exception_t* exc_stack;
    unsigned int exc_stack_size;

    void* call_stack;
    unsigned int call_stack_size;
} Yarn_t;

void init_yarn(Yarn_t* yarn, Exception_t* exc_stack, unsigned int exc_stack_size, void *call_stack, unsigned int call_stack_size);

void inline __attribute__((always_inline)) enter_yarn(Yarn_t* yarn);
int inline __attribute__((always_inline)) save_yarn(Yarn_t* yarn);

void resume_yarn(Yarn_t* yarn);

#endif