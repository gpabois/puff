#include <puff/async/loop.h>
#include <puff/async/command.h>

void init_loop(EventLoop_t* loop) {
    init_coro_queue(&loop->ready, loop->__ready, EVENT_LOOP_READY_LEN);
    init_async_timer_queue(&loop->timers, loop->__timers, EVENT_LOOP_TIMER_LEN);
}

void step_loop(EventLoop_t* loop) {
    __step_timers(loop);
    __step_ready(loop);
}

void __process_command(EventLoop_t* loop, Coro_t* coro, AsyncCommand_t* cmd) {
    switch (cmd->type) {
        case AsyncTimerCmd:
            AsyncTimer_t* timer = cmd->arg.timer;
            timer->coro = coro;

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
            __process_command(loop, coro, &cmd);
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
    LockedCoroQueue_t lock = lock_coro_queue(&loop->ready);
    for(Coro_t* ready; dequeue_locked_coro_queue(&lock, &ready);) {
        __loop_send_to_gen(loop, ready);
    }
}

