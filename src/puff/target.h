/**
 * @file target.h
 * @author Gaël PABOIS
 * @brief Define target-related macros
 * @version 0.1
 * @date 2023-09-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __TARGET_H__

#ifdef __ESP8266__
#define __ESP__
#endif

#ifdef __ESP__
#define __XTENSA_LX106__
#endif

#endif