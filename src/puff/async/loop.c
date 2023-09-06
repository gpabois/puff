#include <puff/async/loop.h>
#include <puff/async/command.h>

char __pop_ready(Coro_t** coro);

void __process_command(EventLoop_t* loop, AsyncCommand_t* cmd) {
    switch (cmd->type) {
        case AsyncTimerCmd:
            AsyncTimer_t* timer = cmd->arg.timer;
            // Go to ready queue directly
            if(timer->t <= clock()) {
                if(!enqueue_coro_queue(&loop->ready, timer->coro))
                    throw(ERR_CORO_OVERFLOW, "cannot add coro to ready's queue of event loop");
            } else
                if(!enqueue_async_timer_queue(&loop->timers, timer))
                    throw(ERR_TIMER_OVERFLOW, "cannot add timer to event loop");
            
        break;
    }
}

void __loop_send_to_gen(EventLoop_t* loop, Coro_t* coro) {
    switch (__send_to_gen(coro)) {
        case Gen_Yield:
            AsyncCommand_t cmd;
            __gen_get_val(coro, cmd);
            __process_command(loop, &cmd);
            break;
        case Gen_Returned:
            coro->rc--;
            break;
    }
}

void __step_timers(EventLoop_t* loop) {
    LockedAsyncTimerQueue_t queue = lock_async_timer_queue(&loop->timers);
    for(AsyncTimer_t* timer; dequeue_locked_async_timer_queue(&queue, &timer);) {
        if(timer->t <= clock()) {
            __loop_send_to_gen(loop, timer->coro);
        } else {
            if(!enqueue_async_timer_queue(&loop->timers, timer)) {
                throw(ERR_TIMER_OVERFLOW, "cannot add timer to event loop");
            }
        }
    }
}

void __step_ready(EventLoop_t* loop) {
    for(Coro_t* ready; __pop_ready(&ready);) {
        __loop_send_to_gen(loop, ready);
    }
}

void step_loop(EventLoop_t* loop) {
    __step_timers(loop);
    __step_ready(loop);
}