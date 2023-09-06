#include <puff/error.h>
#include <puff/std/stdio.h>

void vsprintf_error(Error_t* dest, const char* fmt, va_list args) {
    vsprintf_s(dest->msg, ERROR_MAX_SIZE, fmt, args);
}

void copy_error(Error_t* dest, const Error_t* src) {
    dest->code = src->code;
    memmove(dest->msg, src->msg, ERROR_MAX_SIZE);
}