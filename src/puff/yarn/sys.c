#include <puff/yarn/sys.h>
#include <puff/cpu/cpu.h>
#include <puff/exception/context.h>
#include <puff/func/stack.h>

static Yarn_t* stack[_CPU_LEN][MAX_NUMBER_OF_YARN_PER_CPU];
static Yarn_t* tos[_CPU_LEN];

void __init_yarn_sys() {
    printk("Initialise YARN");
    for(_CPU_ID_TYPE cpuid = 0; cpuid < _CPU_LEN; cpuid++) {
        tos[cpuid] = 0;
    }
}

int push_yarn(Yarn_t* yarn) {
    _CPU_ID_TYPE cpuid = getcpu();

    Yarn_t** tos = tos[cpuid];
    
    if(tos > &stack[cpuid][MAX_NUMBER_OF_YARN_PER_CPU])
        throw(ERR_YARN_OVERFLOW, "yarn stack overflow");

    if(*tos == 0) {
        tos = stack[cpuid][0];
    } else {
        tos++;
    }

    *tos = yarn;
}

void pop_and_resume_yarn(int code) {
    Yarn_t* curr = __pop_yarn();
    resume_yarn(curr, code);
}


Yarn_t* __curr_yarn() {
    return tos[getcpu()];
}

Yarn_t* __pop_yarn() {
    Yarn_t** tos = tos[getcpu()];

    if(*tos == 0)
        throw(ERR_YARN_UNDERFLOW, "yarn stack underflow");

    Yarn_t* curr = *tos;
    tos--;
    
    if(tos < stack[getcpu()])
        *tos = 0;
    
    return curr;
}

