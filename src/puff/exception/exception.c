#include <puff/exception/exception.h>
#include <puff/exception/stack.h>
#include <puff/std/setjmp.h>
#include <puff/cpu/cpu.h>
#include <puff/exception/panic.h>

ExceptionStack_t* __assert_exception_stack_exist() {
    ExceptionStack_t* curr = __get_current_exception_stack();
    
    if(curr == 0)
        panic("no exception context is set...");

    return curr;
}

void __assert_no_overflow() {
    ExceptionStack_t* curr = __assert_exception_stack_exist();
    if (curr->tos >= &curr->base[curr->size]) {
        panic("exception's stack overflow");
    }
}

/**
 * Push an exception block.
*/
void __push_exception() {
    ExceptionStack_t* curr = __assert_exception_stack_exist();
    
    if(curr == 0)
        panic("no exception context is set...");
    
    if(curr->tos == 0) 
        curr->tos = &curr->base[0];
    else 
        curr->tos++;

    __assert_no_overflow();
}

void clear_exception() {
    ExceptionStack_t* curr = __assert_exception_context_exist();

    if(curr->tos == &curr->base[0]) 
        curr->tos = 0;
    else
        curr->tos--;
}

char try_exception() {
    ExceptionStack_t* curr = __assert_exception_context_exist();
    __push_exception();
    return setjmp(curr->tos->caller);
}

void throw_exception() {
    ExceptionStack_t* curr = __assert_exception_context_exist();
    longjmp(curr->tos->caller, 1);
}

Exception_t* current_exception() {
    ExceptionStack_t* curr = __assert_exception_context_exist();
    return curr->tos;
}

