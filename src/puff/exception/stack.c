#include <puff/exception/stack.h>
#include <puff/cpu/cpu.h>

static Exception_t default_exc_stacks[_CPU_LEN][DEFAULT_EXCEPTION_STACK_SIZE];
static ExceptionStack_t default_contexts[_CPU_LEN];
static ExceptionStack_t* current_contexts[_CPU_LEN];

void __init_exception_sys()
{
    for(_CPU_ID_TYPE cpuid = 0; cpuid < _CPU_LEN; cpuid++) {
        init_exception_context(&default_contexts[cpuid], default_exc_stacks[cpuid], DEFAULT_EXCEPTION_STACK_SIZE);
    }
}

void set_exception_stack(ExceptionStack_t* ctx)
{
    current_contexts[getcpu()] = ctx;
}

ExceptionStack_t* restore_exception_stack() {
    current_contexts[getcpu()] = &default_contexts[getcpu()];
}
