#ifndef __PRINTK_H__
#define __PRINTK_H__

#if defined(__x86_64__)
#include <puff/std/stdio.h>

#define printk(fmt, ...) printf(fmt, __VA_ARGS__)

#elif defined(__ESP__)
#include <osapi.h>

#define printk(fmt, ...) os_printf(fmt, __VA_ARGS__)

#else
#error "unsupported platform"
#endif