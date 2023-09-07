#ifndef __FUNC_STACK_H__
#define __FUNC_STACK_H__

typedef struct {
    void *bsp;
    unsigned int size;
} CallStack_t;

/**
 * @brief Change the current stack pointer.
 */
void inline __attribute__((always_inline)) set_call_stack(CallStack_t* context);

#endif