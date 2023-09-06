#include <puff/async/timer.h>
#include <puff/async/loop.h>

// Zero-overhead sleep
#define await_sleep(ms) {\
    AsyncTimer_t timer = {\
        .coro = current_coro,\
        .t = clock() + ms * 1000 / CLOCKS_PER_SEC\
    };\
    yield(async_timer(&timer));\
}

async_def(char, async_sleep, int, ms) {
    await_sleep(ms);
    return 1;
}