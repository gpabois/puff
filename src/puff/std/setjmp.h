#ifndef __ABI_SETJMP_H__
#define __ABI_SETJMP_H__

#ifdef __XTENSA_CALL0_ABI__
#include <puff/abi/xtensa-lx106/jmp_buf.h>
#endif 

typedef _JBTYPE jmp_buf[_JBLEN];

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);

#endif 
