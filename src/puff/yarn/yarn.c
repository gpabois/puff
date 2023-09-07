#include <puff/yarn/yarn.h>
#include <puff/func/stack.h>
#include <puff/exception/sys.h>

void init_yarn(Yarn_t* yarn, ExceptionContext_t* exc_context, CallStack_t* call_stack) {
    yarn->exc_ctx = exc_context;
    yarn->stack = call_stack;
}

Yarn_t from_here() {
    Yarn_t yarn;
    yarn.exc_ctx = __get_current_exception_context();
    return yarn;
}

void enter_yarn(Yarn_t* yarn) {
    set_call_stack(yarn->stack);
    set_exception_stack(yarn->exc_ctx);
}

int save_yarn(Yarn_t* yarn) {
    return setjmp(yarn->ctx);
}

void resume_yarn(Yarn_t* yarn, int code) {
    set_exception_context(&yarn->exc_ctx);
    longjmp(yarn->ctx, code);
}