#include <puff/abi/stack.h>

#ifdef __XTENSA_CALL0_ABI__
void switch_stack(void *bsp, unsigned int size) {
    register unsigned int *sp asm("a1");
    *sp = (unsigned int)bsp + size;
}
#endif
