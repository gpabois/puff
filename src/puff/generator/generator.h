#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <puff/yarn/yarn.h>
#include <puff/std/stdint.h>

#define _GEN_BUF_LEN 1000
#define _GEN_STACK_LEN 1000

typedef uint8_t GeneratorBuffer_t[_GEN_BUF_LEN];
typedef uint8_t GeneratorStack_t[_GEN_STACK_LEN];

char Gen_Yield = 0x1;
char Gen_Returned = 0x2;
char Gen_Failed = 0x3;

typedef struct {
    uint8_t data[_GEN_BUF_LEN];
    unsigned int size;
} GeneratorBuffer_t;

typedef struct {
    Yarn_t            yarn;
    GeneratorBuffer_t buf;
    GeneratorStack_t  stack;
} Generator_t;

#define __gen_set_val(gen, rvalue) {\
    typeof(expr)* tbuf = (typeof(expr)*)gen->buf->data;\
    *tbuf = rvalue;\
    gen->buf->size = sizeof(typeof(expr));\
}

#define __gen_get_val(gen, lvalue) {\
    typeof(lvalue)* tbuf = (typeof(lvalue)*)gen->buf->data;\
    lvalue = *tbuf;\
}

/**
 * Send value to the generator.
*/
#define gen_send(gen, lvalue, rvalue) {\
    __gen_set_val(gen, rvalue);\
    int code = __send_generator(gen);\
    if (code == Gen_Yield || code == Gen_Returned) {\
        __gen_get_val(gen, lvalue);\
    }\
}

#define yield(lvalue, rvalue) {\
    __gen_set_val(__gen, rvalue);\
    __ret_from_gen(__gen, Gen_Yield);\
    read_gen(__gen, lvalue);\
}

#define yield_from(from_expr) {\
    Generator_t* from = from_expr;\
    __yield_from(__gen, from);\
}\

void __yield_from(Generator_t* caller, Generator_t* callee);

/**
 * After value is set, send it to the generator and run it.
 * Throw an error if the generator encounter an exception.
*/
char __send_gen(Generator_t* gen);
/**
 * Returns back to the __send_gen call.
*/
void __ret_from_gen(Generator_t* gen, int code);

/**
 * Move the value stored in the generator buffer from src to dest.
*/
void __move_gen_buf(Generator_t* dest, Generator_t* src);

/**
 * Throw the error stored in the generator buffer.
*/
void __rethrow_gen_error(Generator_t* gen);

#endif