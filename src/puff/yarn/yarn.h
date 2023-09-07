#ifndef __YARN_D_H__
#define __YARN_D_H__

#include <puff/exception/exception.h>
#include <puff/exception/sys.h>
#include <puff/func/stack.h>

/**
 * @brief Easy execution flows switch
*/
typedef struct {
    jmp_buf ctx;
    ExceptionContext_t* exc_ctx;
    CallStack_t* stack;
} Yarn_t;


/**
 * @brief Initialise a yarn.
 */
void init_yarn(Yarn_t* yarn, ExceptionContext_t* exc_context, CallStack_t* call_stack);

/**
 * @brief Returns the yarn corresponding to the current execution point.
 * 
 * @return Yarn_t 
 */
Yarn_t from_here();

/**
 * @brief Initialise an independant execution flow.
 * 
 * @note
 * The operations performed are :
 *  - Change the stack pointer ;
 *  - Change the exception context.
 */
void inline __attribute__((always_inline)) enter_yarn(Yarn_t* yarn);

/**
 * @brief Save current execution point to the yarn.
 * 
 * @param yarn
 */
int inline __attribute__((always_inline)) save_yarn(Yarn_t* yarn);

/**
 * @brief Resume the execution saved in the yarn.
 * 
 * @param yarn
 */
void resume_yarn(Yarn_t* yarn, int code);

#endif