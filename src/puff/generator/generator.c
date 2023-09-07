#include <puff/generator/generator.h>
#include <puff/std/string.h>
#include <puff/yarn.h>

void __init_gen(Generator_t* gen) {
    gen->rc = 1;
    
    gen->exc_context.base = &gen->__exc_stack[0];
    gen->exc_context.size = GEN_EXCEPTION_STACK_LEN;

    gen->call_stack.bsp = &gen->__call_stack[0];
    gen->call_stack.size = GEN_STACK_LEN;

    init_yarn(&gen->yarn, &gen->exc_context, &gen->call_stack);
}

void __yield_from(Generator_t* caller, Generator_t* callee, char yield_on_return) {
    int fromCode;
    __gen_set_val(caller, (void*)0);
    
    do {
        __move_gen_value(caller, callee);
        fromCode = __send_gen(callee);
        
        switch(fromCode) {
            case Gen_Yield:
                __move_gen_value(callee, caller);
                __ret_from_gen(caller, Gen_Yield);
            break;
            case Gen_Returned:
                if(yield_on_return) {
                    __move_gen_value(callee, caller);
                    __ret_from_gen(caller, Gen_Yield);
                }
            break;
        }

    } while(fromCode == Gen_Yield);
}

void __ret_from_gen(Generator_t* gen, int code) {
    pop_and_resume_yarn(code);
}

char __send_gen(Generator_t* gen) {
    Yarn_t here = from_here();
    int code = push_yarn(&here);

    switch(code) {
        case 0:
            resume_yarn(&gen->yarn, 1);
        break;
        case Gen_Failed:
             __rethrow_gen_error(gen);
        break;
    } 

    return code;
}

/**
 * Move the value stored in the generator buffer from src to dest.
*/
static void __move_gen_buf(Generator_t* dest, const Generator_t* src) {
    memmove(dest->buf.data, src->buf.data, src->buf.size);
    dest->buf.size = src->buf.size;
}

/**
 * Rethrow the error stored in the generator's buffer.
*/
static void __rethrow_gen_error(Generator_t* gen)
{
    // Get the error
    Error_t* err = (Error_t*)gen->buf.data;
    // Throw the error
    throw_err(err);
}