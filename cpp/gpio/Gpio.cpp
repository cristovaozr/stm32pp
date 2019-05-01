/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

#include "Gpio.h"
#include "stm32f4xx_ll_bus.h"

#include <cstdint>

using namespace GPIO;

Gpio::Gpio(GPIO_TypeDef *gpio, GPIO::Name pin) : p_gpio(gpio), p_pin(pin)
{
    uint32_t periphs = 0x00000000;

    // Enables the corresponding power to the GPIO port
    if(this->p_gpio == GPIOA)       periphs = LL_AHB1_GRP1_PERIPH_GPIOA;
    else if(this->p_gpio == GPIOB)  periphs = LL_AHB1_GRP1_PERIPH_GPIOB;
    else if(this->p_gpio == GPIOC)  periphs = LL_AHB1_GRP1_PERIPH_GPIOC;
    else if(this->p_gpio == GPIOD)  periphs = LL_AHB1_GRP1_PERIPH_GPIOD;
    else if(this->p_gpio == GPIOE)  periphs = LL_AHB1_GRP1_PERIPH_GPIOE;
    else if(this->p_gpio == GPIOF)  periphs = LL_AHB1_GRP1_PERIPH_GPIOF;
    else if(this->p_gpio == GPIOG)  periphs = LL_AHB1_GRP1_PERIPH_GPIOG;
    else if(this->p_gpio == GPIOH)  periphs = LL_AHB1_GRP1_PERIPH_GPIOH;
    else if(this->p_gpio == GPIOI)  periphs = LL_AHB1_GRP1_PERIPH_GPIOI;

    LL_AHB1_GRP1_EnableClock(periphs);
}

Gpio::Gpio(const Gpio &c) : Gpio(c.p_gpio, c.p_pin) {}

Gpio::~Gpio()
{
    LL_GPIO_DeInit(this->p_gpio);
}

void Gpio::operator=(GPIO::Value v)
{
    this->Write(v);
}

void Gpio::SetMode(GPIO::Mode mode)
{
    LL_GPIO_SetPinMode(this->p_gpio, this->p_pin, (uint32_t)mode);
}

void Gpio::SetPullUp(GPIO::PullMode mode)
{
    LL_GPIO_SetPinPull(this->p_gpio, this->p_pin, (uint32_t)mode);
}

void Gpio::SetOutputMode(GPIO::OutputMode mode)
{
    LL_GPIO_SetPinOutputType(this->p_gpio, this->p_pin, (uint32_t)mode);
}

void Gpio::SetSpeed(GPIO::Speed speed)
{
    LL_GPIO_SetPinSpeed(this->p_gpio, this->p_pin, (uint32_t)speed);
}

GPIO_TypeDef *Gpio::GetGPIO()
{
    return this->p_gpio;
}

GPIO::Name Gpio::GetPin()
{
    return this->p_pin;
}
