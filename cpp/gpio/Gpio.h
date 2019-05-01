/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

#ifndef GPIO_H_
#define GPIO_H_

#include <cstdint>
#include "stm32f4xx.h"
#include "stm32f4xx_ll_gpio.h"

namespace GPIO {

typedef enum {
    RESET = 0,
    SET
} Value;

typedef enum {
    PIN_0 = LL_GPIO_PIN_0,
    PIN_1 = LL_GPIO_PIN_1,
    PIN_2 = LL_GPIO_PIN_2,
    PIN_3 = LL_GPIO_PIN_3,
    PIN_4 = LL_GPIO_PIN_4,
    PIN_5 = LL_GPIO_PIN_5,
    PIN_6 = LL_GPIO_PIN_6,
    PIN_7 = LL_GPIO_PIN_7,
    PIN_8 = LL_GPIO_PIN_8,
    PIN_9 = LL_GPIO_PIN_9,
    PIN_10 = LL_GPIO_PIN_10,
    PIN_11 = LL_GPIO_PIN_11,
    PIN_12 = LL_GPIO_PIN_12,
    PIN_13 = LL_GPIO_PIN_13,
    PIN_14 = LL_GPIO_PIN_14,
    PIN_15 = LL_GPIO_PIN_15,
} Name;

typedef enum {
    INPUT       = LL_GPIO_MODE_INPUT,
    OUTPUT      = LL_GPIO_MODE_OUTPUT,
    ANALOG      = LL_GPIO_MODE_ANALOG,
    ALTERNATE   = LL_GPIO_MODE_ALTERNATE
} Mode;

typedef enum
{
    NOPULL      = LL_GPIO_PULL_NO,
    PULLUP      = LL_GPIO_PULL_UP,
    PULLDOWN    = LL_GPIO_PULL_DOWN
} PullMode;

typedef enum
{
    PUSHPULL    = LL_GPIO_OUTPUT_PUSHPULL,
    OPENDRAIN   = LL_GPIO_OUTPUT_OPENDRAIN
} OutputMode;

typedef enum
{
    LOW         = LL_GPIO_SPEED_FREQ_LOW,
    MEDIUM      = LL_GPIO_SPEED_FREQ_MEDIUM,
    HIGH        = LL_GPIO_SPEED_FREQ_HIGH,
    VERYHIGH    = LL_GPIO_SPEED_FREQ_VERY_HIGH
} Speed;

class Gpio {
public:

    explicit Gpio(GPIO_TypeDef *gpio, GPIO::Name pin);
    Gpio(const Gpio&c);
    virtual ~Gpio();

    virtual void Write(GPIO::Value v) = 0;
    virtual GPIO::Value Read() = 0;
    
    void operator=(GPIO::Value v);

    void SetMode(GPIO::Mode mode);
    void SetPullUp(GPIO::PullMode mode);
    void SetOutputMode(GPIO::OutputMode mode);
    void SetSpeed(GPIO::Speed speed);

    GPIO_TypeDef *GetGPIO();
    GPIO::Name GetPin();

protected:
    GPIO_TypeDef *p_gpio;
    GPIO::Name p_pin;
    // TODO: add treatment for ISR
};

}; // namespace GPIO

#endif
