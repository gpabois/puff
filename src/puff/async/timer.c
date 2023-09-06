#include <puff/async/timer.h>
#include <puff/async/loop.h>

async_def(char, async_sleep, int, ms) {
    AsyncTimer_t timer = {
        .coro = current_coro,
        .t = clock() + ms * 1000 / CLOCKS_PER_SEC
    };
    
    yield(async_timer(&timer));
    
    return 1;
}