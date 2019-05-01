/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

#include "Gpio.h"
#include "OutputGpio.h"
#include "Usart.h"

int main(void)
{
    GPIO::OutputGpio led(GPIOF, GPIO::PIN_6);
    GPIO::OutputGpio led2(GPIOF, GPIO::PIN_8);

    USART::ConfigStruct config = {
        .Baudrate = 115200,
        .Parity = USART::NONE,
        .StopBits = USART::ONE,
        .HardwareFlowControl = USART::HW_NONE
    };
    USART::Usart serial(USART2, config);

    led.Write(GPIO::SET);
    led2.Write(GPIO::SET);

    serial.Write("Hello world!\r\n", 14);

    while(true);

    return 0;
}

