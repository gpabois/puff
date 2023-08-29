#include "../stack.h"
#include "./registers.h"

void switch_stack(void *bsp, unsigned int size) {
    // call0 convention.
    a1 = bsp + size;
}
