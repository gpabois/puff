#include <puff/yarn/yarn.h>
#include <puff/func/stack.h>
#include <puff/exception/context.h>

void init_yarn(Yarn_t* yarn, Exception_t* exc_stack, unsigned int exc_stack_size, void *call_stack, unsigned int call_stack_size) {
    yarn->exc_stack = exc_stack;
    yarn->exc_stack_size = exc_stack_size;
    yarn->call_stack = call_stack;
    yarn->call_stack_size = call_stack_size;
}

void enter_yarn(Yarn_t* yarn) {
    set_call_stack(yarn->call_stack, yarn->call_stack_size);
    set_exception_stack(yarn->exc_stack);
}

int save_yarn(Yarn_t* yarn) {
    restore_exception_stack();
    return setjmp(yarn->call_stack);
}

void resume_yarn(Yarn_t* yarn) {
    set_exception_context(yarn->exc_stack);
    longjmp(yarn->ctx, 1);
}