#include <puff/yarn/yarn.h>
#include <puff/func/stack.h>
#include <puff/exception/sys.h>

void init_yarn(Yarn_t* yarn, Exception_t* exc_stack, unsigned int exc_stack_size, void *call_stack, unsigned int call_stack_size) {
    init_exception_context(&yarn->exc_ctx, exc_stack, exc_stack_size);
    yarn->call_stack = call_stack;
    yarn->call_stack_size = call_stack_size;
}

Yarn_t from_here() {
    Yarn_t yarn;
    yarn.exc_ctx = *__get_current_exception_context();
    return yarn;
}

void enter_yarn(Yarn_t* yarn) {
    set_call_stack(yarn->call_stack, yarn->call_stack_size);
    set_exception_stack(yarn->exc_ctx);
}

int save_yarn(Yarn_t* yarn) {
    return setjmp(yarn->ctx);
}

void resume_yarn(Yarn_t* yarn) {
    longjmp(yarn->ctx, 1);
}