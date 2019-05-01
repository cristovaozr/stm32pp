/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

#include "OutputGpio.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_gpio.h"

using namespace GPIO;

OutputGpio::OutputGpio(GPIO_TypeDef *gpio, GPIO::Name pin) : Gpio(gpio, pin)
{
    LL_GPIO_InitTypeDef initstruct = {
        .Pin = (uint32_t)this->p_pin,
        .Mode = LL_GPIO_MODE_OUTPUT,
        .Speed = LL_GPIO_SPEED_FREQ_LOW,
        .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
        .Pull = LL_GPIO_PULL_NO,
        .Alternate = LL_GPIO_AF_0
    };

    LL_GPIO_Init(this->p_gpio, &initstruct);
}

OutputGpio::OutputGpio(const OutputGpio &c) : OutputGpio(c.p_gpio, c.p_pin) {}

OutputGpio::~OutputGpio() {}

GPIO::Value OutputGpio::Read()
{
    GPIO::Value val = RESET;
    if(LL_GPIO_IsOutputPinSet(this->p_gpio, this->p_pin))   val = SET;

    return val;
}

void OutputGpio::Write(GPIO::Value val)
{
    if(val == RESET) LL_GPIO_ResetOutputPin(this->p_gpio, this->p_pin);
    else LL_GPIO_SetOutputPin(this->p_gpio, this->p_pin);
}
