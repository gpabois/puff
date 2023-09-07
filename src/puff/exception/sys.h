#ifndef __EXCEPTION_SYS_H__
#define __EXCEPTION_SYS_H__

#include <puff/exception/context.h>
#include <puff/cpu/cpu.h>

#define DEFAULT_EXCEPTION_STACK_SIZE 100

/**
 * @brief Initialise the exception system.
 * @note
 * Must be called at the start of the firmware execution.
 */
void __init_exception_sys();

/**
 * @brief Set the current exception context
 * 
 * @param ctx 
 */
void set_exception_context(ExceptionContext_t* ctx);

/**
 * @brief Restore the default exception context
 * 
 * @return ExceptionContext_t* 
 */
ExceptionContext_t* restore_exception_context();

/**
 * @brief Get the current exception context
 * @internal
 * 
 * @return ExceptionContext_t* 
 */
ExceptionContext_t* __get_current_exception_context();

#endif