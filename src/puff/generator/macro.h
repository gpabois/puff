#ifndef __GEN_MACRO_H__
#define __GEN_MACRO_H__

#include <puff/generator/generator.h>
#include <puff/generator/allocator.h>
#include <puff/exception/exception.h>
#include <puff/error.h>
#include <puff/yarn/yarn.h>

#define gen(return_t) Generator_t*

#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(macro, ...) __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a, b, ...) \
   macro(a, b) \
  __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))

#define FOR_EACH_AGAIN() FOR_EACH_HELPER

#define ARG_IDS_ITEM(a, b) b
#define ARG_DEFS_ITEM(a, b) a b
#define ARG_IDS(...) FOR_EACH(ARG_IDS_ITEM, __VA_ARGS__)
#define ARG_DEFS(...) FOR_EACH(ARG_DEFS_ITEM, __VA_ARGS__)

#define cat(x,y) cat2(x,y)
#define cat2(x,y) x##y
#define IS_VOID   0

/**
* Hack: https://www.scs.stanford.edu/%7Edm/blog/va-opt.html
**/
#define gen_def(return_t, name, ...) Generator_t* name(ARG_DEFS(__VA_ARGS__)) {\
    Generator_t* gen;\
    Yarn_t here = from_here();\
\
    if(!alloc_gen(&gen))\
        throw(0x1, "cannot create generator %s", name);\
\
    if(!push_yarn(&here))\
        __gen_run_##name(gen, ARG_IDS(__VA_ARGS__)); \
\
    return gen;\
}\
static void __gen_run_##name(Generator_t* gen, ARG_DEFS(__VA_ARGS__)) {\
    __init_gen(gen);\
    try {\
        return_t* __t;\
        switch(_Generic(__t, void*: 0, default: 1)) {\
            case 0:\
                __gen_##name(gen, ARG_IDS(__VA_ARGS__));\
            break;\
            case 1:\
                return_t __retval = __gen_##name(gen, ARG_IDS(__VA_ARGS__));\
                __gen_set_val(gen, __retval);\
            break;\
        }\
        __ret_from_gen(gen, Gen_Returned);\
    } catch(error) {\
        __gen_set_val(gen, error);\
        __ret_from_gen(gen, Gen_Failed);\
    } finally\
}\
static return_t __gen_##name(Generator_t* __gen, ARG_DEFS(__VA_ARGS__)) 

#endif