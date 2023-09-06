#include <puff/exception/exception.h>
#include <puff/exception/sys.h>
#include <puff/std/setjmp.h>
#include <puff/std/stdio.h>
#include <puff/cpu/cpu.h>
#include <puff/panic.h>
#include <puff/error.h>

ExceptionContext_t* __assert_context_exist() {
    ExceptionContext_t* curr = __get_current_exception_stack();
    
    if(curr == 0)
        panic("no exception context exist");

    return curr;
}

static void __assert_no_overflow() {
    ExceptionContext_t* curr = __assert_context_exist();
    if (curr->tos >= &curr->base[curr->size])
        panic("exception's stack overflow");
}

/**
 * Push an exception block.
*/
static void __push_exception() {
    ExceptionContext_t* curr = __assert_context_exist();
    
    if(curr->tos == 0) 
        curr->tos = &curr->base[0];
    else 
        curr->tos++;

    __assert_no_overflow();
}

void clear_exception() {
    ExceptionContext_t* curr = __assert_exception_context_exist();

    if(curr->tos == &curr->base[0]) 
        curr->tos = 0;
    else
        curr->tos--;
}

char try_exception() {
    ExceptionContext_t* curr = __assert_exception_context_exist();
    __push_exception();
    return setjmp(curr->tos->caller);
}

void __jmp_throw() {
    ExceptionContext_t* ctx = __assert_exception_context_exist();
    longjmp(ctx->tos->caller, 1);
}

void throw_err(Error_t* err) {
    ExceptionContext_t* ctx = __assert_exception_context_exist();
    ctx->tos->error = *err;
}

void throw(int code, const char *fmt, ...) {
    ExceptionContext_t* ctx = __assert_exception_context_exist();
    
    // Fill the error
    va_list argptr;
    va_start(argptr, fmt);
    ctx->tos->error.code = code;
    vsprintf_error(&ctx->tos->error, fmt, argptr);
    va_end(argptr);

    // Jump back to the caller
    __jmp_throw();
}

Exception_t* __current_exception() {
    ExceptionContext_t* curr = __assert_exception_context_exist();
    return curr->tos;
}

