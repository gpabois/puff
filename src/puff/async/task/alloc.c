#include <puff/async/task/alloc.h>

static AsyncTask_t HEAP[ASYNC_TASK_MAX_SIZE];

char AsyncTask_alloc(AsyncTask_t**dest) {
    for(unsigned int i = 0; i < ASYNC_TASK_MAX_SIZE; i++) {
        if(HEAP[i].rc == 0) { // free task
            AsyncTask_t* task = &HEAP[i];
            acquire_async_task(task);
            *dest = task;
            return 1;
        }
    }
    return 0;
}