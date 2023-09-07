#ifndef __CPU_H__
#define __CPU_H__

#define _CPU_LEN 1
#define _CPU_ID_TYPE char

/**
 * @brief Get the current CPU id for this execution flow.
 * 
 * @return _CPU_ID_TYPE 
 */
_CPU_ID_TYPE getcpu() { return 0; };

#endif