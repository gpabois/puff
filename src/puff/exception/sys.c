#include <puff/exception/sys.h>
#include <puff/cpu/cpu.h>

static Exception_t default_exc_stacks[_CPU_LEN][DEFAULT_EXCEPTION_STACK_SIZE];
static ExceptionContext_t default_contexts[_CPU_LEN];
static ExceptionContext_t* current_contexts[_CPU_LEN];

void __init_exception_sys()
{
    printk("Initialise exception system");
    for(_CPU_ID_TYPE cpuid = 0; cpuid < _CPU_LEN; cpuid++) {
        init_exception_context(&default_contexts[cpuid], default_exc_stacks[cpuid], DEFAULT_EXCEPTION_STACK_SIZE);
    }
}

void set_exception_context(ExceptionContext_t* ctx)
{
    current_contexts[getcpu()] = ctx;
}

ExceptionContext_t* restore_exception_context() {
    current_contexts[getcpu()] = &default_contexts[getcpu()];
}
