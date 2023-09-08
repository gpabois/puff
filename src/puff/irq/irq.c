#include <puff/target.h>

#ifdef __XTENSA_LX106__

/**
 * @brief Reset
 */
void __irq_reset();
/**
 * @brief User-related exception
 * @note
 * PC :         EPC
 * SCRATCH :    EXCSAVE
 * RET :        RFE
 */
void __irq_user_exception();
/**
 * @brief Kernel-related exception
 * @note
 * PC :         EPC
 * SCRATCH :    EXCSAVE
 * RET :        RFE
 */
void __irq_kernel_exception();

/**
 * @brief Double exception
 * @note
 * PC :         DEPC
 * SCRATCH :    EXCSAVE
 * RET :        RFDE 
 */
void __irq_double_exception();

/**
 * @brief Window overflow 4
 * @note
 * PC :     EPC
 * RET :    RFWO
 */
void __irq_window_overflow_4();

/**
 * @brief Window overflow 8
 * @note
 * PC :     EPC
 * RET :    RFWO
 */
void __irq_window_overflow_8();

/**
 * @brief Window overflow 12
 * @note
 * PC :     EPC
 * RET :    RFWO
 */
void __irq_window_overflow_12();

/**
 * @brief Window underflow 4
 * @note
 * PC :     EPC
 * RET :    RFWU
 */
void __irq_window_underflow_4();

/**
 * @brief Window underflow 8
 * @note
 * PC :     EPC
 * RET :    RFWU
 */
void __irq_window_underflow_8();

/**
 * @brief Window underflow 12
 * @note
 * PC :     EPC
 * RET :    RFWU
 */
void __irq_window_underflow_12();
#endif