#ifndef __GPIO_PIN_H__
#define __GPIO_PIN_H__

#include <puff/std/stdint.h>

#define ANALOG 0
#define DIGITAL 1

/**
 * @brief The pin is in read mode
 */
#define READ 0
/**
 * @brief The pin is in write mode.
 */
#define WRITE 1

/**
 * @brief The pin value is constant.
 */
#define CONSTANT 0
/**
 * @brief 
 * 
 */
#define RISING 1
#define FALLING 2

#define PinType_t uint8_t
#define PinMode_t uint8_t
#define PinId_t   uint8_t

typedef struct {
    const char *name;
    PinId_t     id;
    PinType_t   type;
    PinMode_t   mode;
} Pin_t;

#ifdef __ESP8266__
    #define GPIO_LEN 16
    typedef uint8_t PinSize_t;
#else 
    #define GPIO_LEN 0
    typedef uint8_t PinSize_t;
#endif

/**
 * @brief Return the pin behind the number.
 * 
 * @param nb 
 * @return Pin_t* 
 */
Pin_t* pin(PinSize_t nb);