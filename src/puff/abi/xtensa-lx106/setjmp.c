#include <puff/std/setjmp.h>

#ifdef __XTENSA_CALL0_ABI__
void inline __attribute__((always_inline)) __save_regs(jmp_buf env) {
    register unsigned int *a0 asm("a0");
    register unsigned int *a1 asm("a1");
    register unsigned int *a12 asm("a12");
    register unsigned int *a13 asm("a13");
    register unsigned int *a14 asm("a14");
    register unsigned int *a15 asm("a15");

    env[0] = *a0;
    env[1] = *a1;
    env[2] = *a12;
    env[3] = *a13;
    env[4] = *a14;
    env[5] = *a15;
}

void __restore_regs(jmp_buf env) {
    register unsigned int *a0 asm("a0");
    register unsigned int *a1 asm("a1");
    register unsigned int *a12 asm("a12");
    register unsigned int *a13 asm("a13");
    register unsigned int *a14 asm("a14");
    register unsigned int *a15 asm("a15");

    *a0 = env[0];
    *a1 = env[1];
    *a12 = env[2];
    *a13 = env[3];
    *a14 = env[4];
    *a15 = env[5];
}

int setjmp(jmp_buf env) {
    env[6] = 0;
    __save_regs(env);
    asm("movi a2, _jmp;");      // Move the address to label _jmp into a2
    asm("l32i a3, a1, 0");      // Load the address behind env into a3  (sp+0)
    asm("s32i a2, a3, 24");     // Store the PC into env (a2 -> a3+24)
    asm("_jmp:");
    return env[6];
}

void longjmp(jmp_buf env, int val) {
    env[6] = val;
    __restore_regs(env);
    asm("l32i a3, a1, 0");      // Load the address behind env (sp+0) into a3
    asm("l32i a2, a3, 24");     // Load the PC into a2
    asm("jx a2");               // Jump back 
}
#endif

