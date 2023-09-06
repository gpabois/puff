#include <puff/async/loop.h>
#include <puff/async/command.h>

char __pop_ready(Coro_t** coro);

void __process_command(EventLoop_t* loop, AsyncCommand_t* cmd) {
    switch (cmd->type) {
        case AsyncTimerCmd:
            AsyncTimer_t* timer = cmd->arg.timer;
        break;
    }
}

void step_loop(EventLoop_t* loop) 
{
    // Process coro ready to run
    for(Coro_t* ready; __pop_ready(&ready);) {
        switch (__send_to_gen(ready)) {
            case Gen_Yield:
                AsyncCommand_t cmd;
                __gen_get_val(ready, cmd);
                __process_command(loop, &cmd);
                break;
            case Gen_Returned:
                ready->rc--;
                break;
        }
    }
}