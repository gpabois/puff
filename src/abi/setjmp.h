#ifndef __ABI_SETJMP_H__
#define __ABI_SETJMP_H__

#ifdef __XTENSA_CALL0_ABI__
#include "abi/xtensa-lx106/setjmp.h"
#endif 

int setjmp(jmp_buf* env);
void longjmp(jmp_buf* env, int val);

#endif 
