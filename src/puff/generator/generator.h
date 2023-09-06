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
    size_t            rc;
    Yarn_t            yarn;
    GeneratorBuffer_t buf;
    GeneratorStack_t  stack;
} Generator_t;

// [Private] Set value in the generator buffer.
#define __gen_set_val(gen, rvalue) {\
    typeof(rvalue)* tbuf = (typeof(rvalue)*)gen->buf.data;\
    *tbuf = rvalue;\
    gen->buf.size = sizeof(typeof(rvalue));\
}

// [Private] Get value from the generator buffer.
#define __gen_get_val(gen, lvalue) {\
    typeof(lvalue)* tbuf = (typeof(lvalue)*)gen->buf.data;\
    lvalue = *tbuf;\
}

/**
 * Send value to the generator, and runs it.
*/
#define gen_send(gen, lvalue, rvalue) {\
    __gen_set_val(gen, rvalue);\
    int code = __send_to_gen(gen);\
    if (code == Gen_Yield || code == Gen_Returned) {\
        __gen_get_val(gen, lvalue);\
    }\
}

/*
* Yield value, and assign sent value to the lvalue
*/ 
#define yield_assign(lvalue, rvalue) {\
    __gen_set_val(__gen, rvalue);\
    __ret_from_gen(__gen, Gen_Yield);\
    __gen_get_val(__gen, lvalue);\
}

/*
* Yield value
*/ 
#define yield(rvalue) {\
    __gen_set_val(__gen, rvalue);\
    __ret_from_gen(__gen, Gen_Yield);\
}


// Delegate to a sub-generator.
#define yield_from(from_expr) {\
    __yield_from(__gen, from_expr);\
    __gen->rc--;\
}\

/*
*   Initialise the generator.
*/
void __init_gen(Generator_t* gen);

/*
* Delegate to a sub-generator.
*/
void __yield_from(Generator_t* caller, Generator_t* callee);

/**
 * After value is set, send it to the generator and run it.
 * Throw an error if the generator has failed.
*/
char __send_to_gen(Generator_t* gen);

/**
 * Returns back to the __send_gen call.
*/
void __ret_from_gen(Generator_t* gen, int code);

void acquire_gen(Generator_t* gen);
void release_gen(Generator_t* gen);

#endif