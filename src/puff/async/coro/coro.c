#include <puff/async/coro/coro.h>
#include <puff/async/error.h>

#include <puff/std/setjmp.h>
#include <puff/func/stack.h>
#include <puff/exception/exception.h>
#include <puff/yarn/yarn.h>
#include <puff/yarn/stack.h>

void inline __attribute__((always_inline)) __setup_coro(Coroutine_t* coro, jmp_buf caller) {
    init_yarn(
        &coro->yarn, 
        coro->exc_stack, 
        CORO_MAX_EXCEPTION_STACK_SIZE, 
        coro->call_stack, 
        CORO_MAX_CALL_STACK_SIZE
    );
    
    enter_yarn(&coro->yarn);

    if(!save_yarn(&coro->yarn)) {
        longjmp(caller, 1);
    }

    /* Catch any exception. */
    if(try_exception()) {
        copy_error(&coro->error, current_exception()->error);
        clear_exception();
        coro->status |= ASYNC_TASK_FAILED;
        ret_from_async_task();
    }
}

/**
*  Execute the async task
*/
void next_coro(Coroutine_t* coro) {
    Yarn_t here = from_here();
    push_yarn(&here);
    
    if(!save_yarn(&here))
        resume_yarn(&coro->yarn);
}

void ret_from_coro(Coroutine_t* coro) {
    if(!save_yarn(&coro->yarn)) {
        pop_and_resume_yarn();
    }
}