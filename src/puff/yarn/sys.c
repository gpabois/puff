#include <puff/yarn/stack.h>
#include <puff/cpu/cpu.h>
#include <puff/exception/stack.h>
#include <puff/func/stack.h>

static Yarn_t* stack[_CPU_LEN][524];
static Yarn_t* tos[_CPU_LEN];

Yarn_t* __curr_yarn() {
    return tos[getcpu()];
}

Yarn_t* __pop_yarn() {
    Yarn_t* curr = __curr_yarn();

    if(curr == 0) {
        restore_exception_context();
    } else {
        set_exception_stack(curr->exc_stack);
    }
}

void __init_yarn_sys() {
    for(_CPU_ID_TYPE cpuid = 0; cpuid < _CPU_LEN; cpuid++) {
        tos[cpuid] = 0;
    }
}

void push_yarn(Yarn_t* yarn) {
    
}

