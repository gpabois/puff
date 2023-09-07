#include <puff/func/stack.h>

#ifdef __ESP__

#ifdef __XTENSA_CALL0_ABI__
void set_call_stack(CallStack_t stack) {
    register unsigned int *sp asm("a1");
    *sp = (unsigned int)stack.bsp + stack.size;
}
#endif

#else
#error "unsupported platform"
#endif