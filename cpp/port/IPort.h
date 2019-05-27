/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

#ifndef IPORT_H_
#define IPORT_H_

#include <cstdint>
#include "stm32f4xx.h"
#include "stm32f4xx_ll_gpio.h"

namespace GPIO {

class IPort {
public:
    IPort() = default;
    virtual ~IPort();

    virtual uint32_t Read() = 0;
    virtual void Write(uint32_t) = 0;
};

}; // namespace GPIO

#endif