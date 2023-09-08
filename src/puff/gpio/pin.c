#include <puff/gpio/pin.h>

#ifdef __ESP8266__
static Pin_t pins[GPIO_LEN] = {
    {.name = "GPIO0_U", .type=DIGITAL, .id = 15},
    {.name = "U0TXD_U", .type=DIGITAL, .id = 26},
    {.name = "GPIO2_U", .type=DIGITAL, .id = 14},
    {.name = "U0RXD_U", .type=DIGITAL, .id = 25},
    {.name = "GPIO4_U", .type=DIGITAL, .id = 16},
    {.name = "GPIO5_U", .type=DIGITAL, .id = 24},
    {.name = "SD_CLK_U", .type=DIGITAL, .id = 21},
    {.name = "SD_DATA0_U", .type=DIGITAL, .id = 22}, 
    {.name = "SD_DATA1_U", .type=DIGITAL, .id = 23}, 
    {.name = "SD_DATA2_U", .type=DIGITAL, .id = 18}, 
    {.name = "SD_DATA3_U", .type=DIGITAL, .id = 19},
    {.name = "SD_CMD_U", .type=DIGITAL, .id = 20}, 
    {.name = "MTDI_U", .type=DIGITAL, .id = 10}, 
    {.name = "MTCK_U", .type=DIGITAL, .id = 12}, 
    {.name = "MTMS_U", .type=DIGITAL, .id = 9},
    {.name = "MTDO_U", .type=DIGITAL, .id = 13}
};
#else
static Pin_t pins[GPIO_LEN] = {};
#endif

Pin_t* pin(PinSize_t nb) {
    if (nb >= GPIO_LEN ) return 0;
    return &pins[nb];
}
