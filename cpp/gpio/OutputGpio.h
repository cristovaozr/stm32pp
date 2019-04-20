#ifndef OUTPUTGPIO_H_
#define OUTPUTGPIO_H_

#include <cstdint>
#include "stm32f4xx.h"
#include "stm32f4xx_ll_gpio.h"
#include "Gpio.h"

namespace GPIO {

class OutputGpio : public Gpio {

public:
    explicit OutputGpio(GPIO_TypeDef *gpio, GPIO::Name pin);
    OutputGpio(const OutputGpio &c);
    virtual ~OutputGpio();

    virtual void Write(GPIO::Value v) override;
    virtual GPIO::Value Read() override;
};

}; // namespace GPIO

#endif
