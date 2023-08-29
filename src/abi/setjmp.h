#ifndef __ABI_SETJMP_H__
#define __ABI_SETJMP_H__

typedef struct jmp_buf_t jmp_buf;

int setjmp(jmp_buf* env);
void longjmp(jmp_buf* env, int val);

#endif 
