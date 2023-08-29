#include "../setjmp.h"

struct jmp_buf_t {
    unsigned int a[16];   
    unsigned int pc;
    int val;
};

void inline __attribute__((always_inline)) __save_regs(jmp_buf* env) {
    asm("s32i a0, [env->a[0]];");
    asm("s32i a1, [env->a[1]];");
    asm("s32i a2, [env->a[2]];");
    asm("s32i a3, [env->a[3]];");
    asm("s32i a4, [env->a[4]];");
    asm("s32i a5, [env->a[5]];");
    asm("s32i a6, [env->a[6]];");
    asm("s32i a7, [env->a[7]];");
    asm("s32i a8, [env->a[8]];");
    asm("s32i a9, [env->a[9]];");
    asm("s32i a10, [env->a[10]];");
    asm("s32i a11, [env->a[11]];");
    asm("s32i a12, [env->a[12]];");
    asm("s32i a13, [env->a[13]];");
    asm("s32i a14, [env->a[14]];");
    asm("s32i a15, [env->a[15]];");
    asm("s32i pc, [env->pc];");
}

void __restore_regs(jmp_buf* env) {

}

int setjmp(jmp_buf* env) {
    env->val = 0;
    __save_regs(env);
    return env->val;
}

void longjmp(jmp_buf* env, int val) {
    env->val = val;
    __restore_regs(env);
}