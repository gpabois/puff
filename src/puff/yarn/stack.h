#ifndef __YARN_STACK_H__
#define __YARN_STACK_H__

#include <puff/yarn/yarn.h>

// Init YARN system.
void __init_yarn_sys();

// Push yarn, returns when popped.
int push_yarn(Yarn_t* yarn);

void pop_and_resume_yarn(int code);

#endif