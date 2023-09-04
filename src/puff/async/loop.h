#ifndef __ASYNC_EVENT_LOOP_H__
#define __ASYNC_EVENT_LOOP_H__

/*
* Event loop
*/
typedef struct {    
    

} EventLoop_t;

/*
* Add the async task to the event loop.
*/
void add_async_task(EventLoop_t* loop, AsyncTask_t* task);

#endif