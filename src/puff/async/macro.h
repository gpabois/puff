#ifndef __ASYNC_MACRO_H__
#define __ASYNC_MACRO_H__

#include <puff/generator/macro.h>
#include <puff/async/coro.h>

#define async(return_t) Coro_t*
#define async_def(return_t, name, ...) gen_def(return_t, name, __VA_ARGS__)

// Await the value, and assign the returned value.
#define await_assign(coro_expr, lvalue) {\
    Generator_t* coro = coro_expr;\
    __yield_from(__gen, coro);\
    __gen_get_value(coro, lvalue);\
    coro->rc--;\
}\

#define current_coro __gen

#endif