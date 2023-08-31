#ifndef __ABI_XTENSA_LX106_H__
#define __ABI_XTENSA_LX106_H__

#ifdef __XTENSA_CALL0_ABI__
typedef struct {
    unsigned int regs[7];   
    int val;
} jmp_buf;
#endif

#endif