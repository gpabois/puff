#ifndef __GPIO_PIN_H__
#define __GPIO_PIN_H__

#include <puff/std/stdint.h>

#define __PIN_ID_TYPE         uint8_t
#define __PIN_TRANSITION_TYPE uint8_t
#define __PIN_TRANSITION_TYPE uint8_t

#define PIN_RISING  1
#define PIN_FALLING 2
#define PIN_CHANGE  3

typedef __PIN_ID_TYPE PinId_t;
typedef __PIN_TRANSITION_TYPE PinTransitionType_t;

#endif