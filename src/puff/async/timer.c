#include <puff/async/timer.h>
#include <puff/async/loop.h>

async_def(char, async_sleep, int, ms) {
    AsyncTimer_t timer = {
        .coro = current_coro,
        .t = clock() + ms * 1000 / CLOCKS_PER_SEC
    };
    
    EventLoop_t* loop = get_current_loop();
    register_timer(loop, &timer);
    yield(0);
    return 1;
}