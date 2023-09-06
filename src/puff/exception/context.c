#include <puff/exception/context.h>

void init_exception_context(ExceptionContext_t* ctx, Exception_t* base, _EXC_CAPACITY_TYPE capacity) {
    ctx->base =  base;
    ctx->tos = 0;
    ctx->size = capacity;
}