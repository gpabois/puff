#ifndef __ASYNC_GPIO_H__
#define __ASYNC_GPIO_H__

#include <puff/async/macro.h>
#include <puff/gpio/pin.h>

async(PinTransitionType_t) on_gpio_pin_change(PinId_t pin);

#endif