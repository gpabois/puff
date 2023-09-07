#include <puff/async/timer.h>
#include <puff/async/loop.h>

async_def(char, async_sleep, int, ms) {
    await_sleep(ms);
    return 1;
}