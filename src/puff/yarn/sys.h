/**
 * @file sys.h
 * @author Gaël PABOIS
 * @brief Implementation of the yarn system.
 * @version 0.1
 * @date 2023-09-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __YARN_STACK_H__
#define __YARN_STACK_H__

#include <puff/yarn/yarn.h>

#define MAX_NUMBER_OF_YARN_PER_CPU 524

#define ERR_YARN_UNDERFLOW 1
#define ERR_YARN_OVERFLOW 2

/**
* @brief Initialise the yarn system
* @author Gaël PABOIS
*/
void __init_yarn_sys();

/**
* @brief Push a yarn in the stack
* 
* @param yarn 
* @return int 0 if the yarn has not been resumed, else the code sent to *resume_yarn*.
* @throw an error if the stack is full.
*/
int push_yarn(Yarn_t* yarn);

/**
 * @brief Pop the TOS and resume it.
 * 
 * @param code the code sent to resume_yarn call.
 * @throw an error if the stack is empty.
 */
void pop_and_resume_yarn(int code);

#endif