#include "InputGpio.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_gpio.h"

using namespace GPIO;

InputGpio::InputGpio(GPIO_TypeDef *gpio, GPIO::Name pin) : Gpio(gpio, pin)
{
    LL_GPIO_InitTypeDef initstruct = {
        .Pin = (uint32_t)this->p_pin,
        .Mode = LL_GPIO_MODE_INPUT,
        .Speed = LL_GPIO_SPEED_FREQ_LOW,
        .OutputType = 0,
        .Pull = LL_GPIO_PULL_NO,
        .Alternate = 0
    };

    LL_GPIO_Init(this->p_gpio, &initstruct);
}

InputGpio::InputGpio(const InputGpio &c) : InputGpio(c.p_gpio, c.p_pin) {}

InputGpio::~InputGpio() {}

GPIO::Value InputGpio::Read()
{
    GPIO::Value val = RESET;
    if(LL_GPIO_IsInputPinSet(this->p_gpio, this->p_pin))   val = SET;

    return val;
}

void InputGpio::Write(GPIO::Value val) { (void)val; }
