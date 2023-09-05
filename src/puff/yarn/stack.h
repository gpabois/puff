#ifndef __YARN_STACK_H__
#define __YARN_STACK_H__

#include <puff/yarn/yarn.h>

// Init YARN system.
void __init_yarn_sys();

void push_yarn(Yarn_t* yarn);
char pop_yarn(Yarn_t** yarn);

void pop_and_resume_yarn();

#endif