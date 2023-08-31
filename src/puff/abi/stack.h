#ifndef __ABI_STACK_H__
#define __ABI_STACK_H__

/*
    Switch the call stack.
*/
void inline __attribute__((always_inline)) switch_stack(void *bsp, unsigned int size);

#endif