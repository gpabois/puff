#include <puff/generator/generator.h>
#include <puff/yarn/stack.h>

void __yield_from(Generator_t* caller, Generator_t* callee) {
    int fromCode;
    caller->buf.size = 0;

    do {
        fromCode = __send_gen(callee);
        if(fromCode == Gen_Yield || fromCode == Gen_Returned)
            __move_gen_value(callee, caller);

    } while(fromCode == Gen_Yield);

    if(fromCode == Gen_Failed) 
        __rethrow_gen_error(caller);
}

void __ret_from_gen(Generator_t* gen, int code) {
    pop_and_resume_yarn(code);
}

char __send_gen(Generator_t* gen) {
    Yarn_t here = from_here();
    int code = push_yarn(&here);

    if(code == 0) 
        resume_yarn(&gen->yarn);
    
    if(code == Gen_Failed)
        __rethrow_gen_error(gen);

    return code;
}