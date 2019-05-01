/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

#ifndef INPUTGPIO_H_
#define INPUTGPIO_H_

#include <cstdint>
#include "stm32f4xx.h"
#include "stm32f4xx_ll_gpio.h"
#include "Gpio.h"

namespace GPIO {

class InputGpio : public Gpio
{
public:
    explicit InputGpio(GPIO_TypeDef *gpio, GPIO::Name pin);
    InputGpio(const InputGpio &c);
    virtual ~InputGpio();

    virtual void Write(GPIO::Value v) override;
    virtual GPIO::Value Read() override;
};

}; // namespace GPIO
#endif
