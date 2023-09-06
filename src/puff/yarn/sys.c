#include <puff/yarn/sys.h>
#include <puff/cpu/cpu.h>
#include <puff/exception/context.h>
#include <puff/func/stack.h>

static Yarn_t* stack[_CPU_LEN][MAX_NUMBER_OF_YARN_PER_CPU];
static Yarn_t* tos[_CPU_LEN];

Yarn_t* __curr_yarn() {
    return tos[getcpu()];
}

Yarn_t* __pop_yarn() {
    Yarn_t* curr = __curr_yarn();

    if(curr == 0) {
        restore_exception_context();
    } else {
        set_exception_context(&curr->exc_ctx);
    }
}

void __init_yarn_sys() {
    for(_CPU_ID_TYPE cpuid = 0; cpuid < _CPU_LEN; cpuid++) {
        tos[cpuid] = 0;
    }
}

void push_yarn(Yarn_t* yarn) {
    
}

