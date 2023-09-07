#ifndef __GPIO_SYS_H__
#define __GPIO_SYS_H__

#ifdef __ESP__
#define GPIO_LEN 16
#define GPIO_ISR_CB(pinID) gpio##pinID_isr_cb() {
    
}
#else

#endif

#endif