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

    USART::Usart usart1(USART1, config);

    led.Write(GPIO::SET);
    led2.Write(GPIO::SET);

    while(true);

    return 0;
}

