#include <puff/async/task/task.h>
#include <puff/async/error.h>

#include <puff/std/setjmp.h>
#include <puff/func/stack.h>
#include <puff/exception/exception.h>
#include <puff/yarn/yarn.h>

void inline __attribute__((always_inline)) __setup_async_task(AsyncTask_t* task, jmp_buf caller) {
    init_yarn(&task->yarn, task->exc_stack, ASYNC_TASK_MAX_EXCEPTION_STACK_SIZE, task->call_stack, ASYNC_TASK_MAX_CALL_STACK_SIZE);
    enter_yarn(&task->yarn);

    if(!save_yarn(&task->yarn)) {
        longjmp(caller, 1);
    }

    /* Catch any exception. */
    if(try_exception()) {
        copy_error(&task->error, current_exception()->error);
        clear_exception();
        task->status |= ASYNC_TASK_FAILED;
        ret_from_async_task();
    }
}

void exec_async_task(AsyncTask_t* task) {
    resume_yarn(&task->yarn);
} 