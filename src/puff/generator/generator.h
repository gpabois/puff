#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <puff/yarn/yarn.h>
#include <puff/std/stdint.h>

#define GEN_BUF_LEN 1000
#define GEN_STACK_LEN 1000
#define GEN_EXCEPTION_STACK_LEN 1000

typedef uint8_t GeneratorBuffer_t[GEN_BUF_LEN];

#define Gen_Yield 1
#define Gen_Returned 2
#define Gen_Failed 3

typedef struct {
    uint8_t data[GEN_BUF_LEN];
    unsigned int size;
} GeneratorBuffer_t;

typedef struct {
    size_t            rc;
    Yarn_t            yarn;

    GeneratorBuffer_t buf;

    ExceptionContext_t exc_context;
    CallStack_t call_stack;

    Exception_t __exc_stack[100];
    uint8_t __call_stack[GEN_STACK_LEN];
} Generator_t;

/**
 * @brief Set value in the generator buffer.
 * @internal
 */
#define __gen_set_val(gen, rvalue) {\
    typeof(rvalue)* tbuf = (typeof(rvalue)*)gen->buf.data;\
    *tbuf = rvalue;\
    gen->buf.size = sizeof(typeof(rvalue));\
}

/**
* @brief Get value from the generator buffer.
* @internal
*/ 
#define __gen_get_val(gen, lvalue) {\
    typeof(lvalue)* tbuf = (typeof(lvalue)*)gen->buf.data;\
    lvalue = *tbuf;\
}

/**
* @brief Send value to the generator, and runs it.
*
* @throw An error if the generator has failed.
* @param gen the generator which will receive the value.
* @param lvalue the receiver of the yielded value (if any) 
* @param rvalue the value to send to the generator
*/
#define gen_send(gen, lvalue, rvalue) {\
    __gen_set_val(gen, rvalue);\
    int code = __send_to_gen(gen);\
    if (code == Gen_Yield || code == Gen_Returned) {\
        __gen_get_val(gen, lvalue);\
    }\
}

/**
* @brief Yield value, and assign sent value to the lvalue
*
* @param rvalue the value to yield
* @param lvalue the receiver of the sent value
*/ 
#define yield_assign(lvalue, rvalue) {\
    __gen_set_val(__gen, rvalue);\
    __ret_from_gen(__gen, Gen_Yield);\
    __gen_get_val(__gen, lvalue);\
}

/**
* @brief Yield value
*
* @param rvalue the value to yield
*/ 
#define yield(rvalue) {\
    __gen_set_val(__gen, rvalue);\
    __ret_from_gen(__gen, Gen_Yield);\
}


/**
 * @brief Delegate to a sub-generator
 * 
 * @param from_expr an expression that return a sub-generator.
 */
#define yield_from(from_expr) {\
    __yield_from(__gen, from_expr, true);\
    __gen->rc--;\
}\

/**
* @brief Initialise the generator
* @internal
*/
void __init_gen(Generator_t* gen);

/**
* @brief Delegates to a sub-generator.
*
* @internal
* @param caller the parent generator
* @param callee the sub-generator
* @param yield_on_return yield the returned value from the callee
*/
void __yield_from(Generator_t* caller, Generator_t* callee, char yield_on_return);

/**
* @brief Resume generator's execution.
*
* @internal
* @param gen the generator to resume
* @throw generator's error
*/
char __send_to_gen(Generator_t* gen);

/**
* @brief Returns back to the __send_gen call
*
* @param gen the generator
* @param code Gen_Yield, Gen_Failed, Gen_Returned
*/
void __ret_from_gen(Generator_t* gen, int code);

#endif