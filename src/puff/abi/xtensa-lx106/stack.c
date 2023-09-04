#include <puff/func/stack.h>

#ifdef __XTENSA_CALL0_ABI__
void set_call_stack(void *bsp, unsigned int size) {
    register unsigned int *sp asm("a1");
    *sp = (unsigned int)bsp + size;
}
#endif
