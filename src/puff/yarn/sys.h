#ifndef __YARN_STACK_H__
#define __YARN_STACK_H__

#include <puff/yarn/yarn.h>

#define MAX_NUMBER_OF_YARN_PER_CPU 524

// Init YARN system.
void __init_yarn_sys();

// Push yarn, returns when popped.
int push_yarn(Yarn_t* yarn);

// Pop and resume the yarn.
void pop_and_resume_yarn(int code);

#endif