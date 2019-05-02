/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

#include "Usart.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"
#include <cstdint>
#include <cstring>

using namespace USART;

Usart::Usart(USART_TypeDef *usart, const USART::ConfigStruct &config) : p_usart(usart)
{
    memcpy(&this->p_config, &config, sizeof(USART::ConfigStruct));

    LL_RCC_ClocksTypeDef rcc_clocks;

    LL_RCC_GetSystemClocksFreq(&rcc_clocks);
    if (this->p_usart == USART1) {
        this->p_PeriphClk = rcc_clocks.PCLK2_Frequency;
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

        // GPIOA_9 = TX, GPIOA_10 = RX, GPIOA_11 = CTS, GPIOA_12 = RTS
        LL_GPIO_InitTypeDef initstruct = {
            .Pin = LL_GPIO_PIN_9 | LL_GPIO_PIN_10,
            .Mode = LL_GPIO_MODE_ALTERNATE,
            .Speed = LL_GPIO_SPEED_FREQ_LOW,
            .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
            .Pull = LL_GPIO_PULL_NO,
            .Alternate = LL_GPIO_AF_7
        };
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
        LL_GPIO_Init(GPIOA, &initstruct);
        // TODO: no hardware flow control enabled right now

    }
    else if (this->p_usart == USART2) {
        this->p_PeriphClk = rcc_clocks.PCLK1_Frequency;
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

        // GPIOD_5 = TX, GPIOD_6 = RX, GPIOA_0 = CTS, GPIOA_1 = RTS
        LL_GPIO_InitTypeDef initstruct = {
            .Pin = LL_GPIO_PIN_5 | LL_GPIO_PIN_6,
            .Mode = LL_GPIO_MODE_ALTERNATE,
            .Speed = LL_GPIO_SPEED_FREQ_LOW,
            .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
            .Pull = LL_GPIO_PULL_NO,
            .Alternate = LL_GPIO_AF_7
        };
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
        LL_GPIO_Init(GPIOD, &initstruct);
        // TODO: no hardware flow control enabled right now
    }
#if defined(USART3)
    else if (this->p_usart == USART3) {
        this->p_PeriphClk = rcc_clocks.PCLK1_Frequency;
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);

        // GPIOB_10 = TX, GPIOB_11 = RX, GPIOB_13 = CTS, GPIOB_14 = RTS
        LL_GPIO_InitTypeDef initstruct = {
            .Pin = LL_GPIO_PIN_10 | LL_GPIO_PIN_11,
            .Mode = LL_GPIO_MODE_ALTERNATE,
            .Speed = LL_GPIO_SPEED_FREQ_LOW,
            .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
            .Pull = LL_GPIO_PULL_NO,
            .Alternate = LL_GPIO_AF_7
        };
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
        LL_GPIO_Init(GPIOB, &initstruct);
        // TODO: no hardware flow control enabled right now
    }
#endif /* USART3 */
#if defined(USART6)
    else if (this->p_usart == USART6) {
        this->p_PeriphClk = rcc_clocks.PCLK2_Frequency;
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6);

        // GPIOC_6 = TX, GPIOC_7 = RX
        LL_GPIO_InitTypeDef initstruct = {
            .Pin = LL_GPIO_PIN_6 | LL_GPIO_PIN_7,
            .Mode = LL_GPIO_MODE_ALTERNATE,
            .Speed = LL_GPIO_SPEED_FREQ_LOW,
            .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
            .Pull = LL_GPIO_PULL_NO,
            .Alternate = LL_GPIO_AF_8
        };
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
        LL_GPIO_Init(GPIOC, &initstruct);
    }
#endif /* USART6 */
#if defined(UART4)
    else if (this->p_usart == UART4) {
        this->p_PeriphClk = rcc_clocks.PCLK1_Frequency;
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);

        // GPIOC_10 = TX, GPIOC_11 = RX
        LL_GPIO_InitTypeDef initstruct = {
            .Pin = LL_GPIO_PIN_10 | LL_GPIO_PIN_11,
            .Mode = LL_GPIO_MODE_ALTERNATE,
            .Speed = LL_GPIO_SPEED_FREQ_LOW,
            .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
            .Pull = LL_GPIO_PULL_NO,
            .Alternate = LL_GPIO_AF_8
        };
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
        LL_GPIO_Init(GPIOC, &initstruct);
    }
#endif /* UART4 */
#if defined(UART5)
    else if (this->p_usart == UART5) {
        this->p_PeriphClk = rcc_clocks.PCLK1_Frequency;
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);

        // GPIOC_12 = TX, GPIOD_2 = RX
        LL_GPIO_InitTypeDef initstruct = {
            .Pin = LL_GPIO_PIN_12,
            .Mode = LL_GPIO_MODE_ALTERNATE,
            .Speed = LL_GPIO_SPEED_FREQ_LOW,
            .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
            .Pull = LL_GPIO_PULL_NO,
            .Alternate = LL_GPIO_AF_8
        };
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
        LL_GPIO_Init(GPIOC, &initstruct);

        initstruct.Pin = LL_GPIO_PIN_2;
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
        LL_GPIO_Init(GPIOD, &initstruct);
    }
#endif /* UART5 */

    LL_USART_InitTypeDef initstruct = {
        .BaudRate = this->p_config.Baudrate,
        .DataWidth = LL_USART_DATAWIDTH_8B,
        .StopBits = this->p_config.StopBits,
        .Parity = this->p_config.Parity,
        .TransferDirection = LL_USART_DIRECTION_TX_RX,
        .HardwareFlowControl = this->p_config.HardwareFlowControl,
        .OverSampling = LL_USART_OVERSAMPLING_16
    };

    LL_USART_Init(this->p_usart, &initstruct);
    LL_USART_Enable(this->p_usart);
}

Usart::Usart(const Usart &c) : Usart(c.p_usart, c.p_config) {}

Usart::~Usart()
{
    LL_USART_Disable(this->p_usart);
    LL_USART_DeInit(this->p_usart);
}

size_t Usart::Write(const void *data, size_t size)
{
    size_t i;
    const uint8_t *udata = static_cast<const uint8_t *>(data);

    for(i = 0; i < size; i++) {
        Write(udata[i]);
    }

    return i;
}

size_t Usart::Read(void *data, size_t size)
{
    size_t i;
    uint8_t *udata = static_cast<uint8_t *>(data);;

    for(i = 0; i < size; i++) {
        udata[i] = Read();
    }

    return i;
}

void Usart::Write(uint8_t c)
{
    while(!isWriteable());
    LL_USART_TransmitData8(this->p_usart, c);
}

uint8_t Usart::Read()
{
    while(!isReadable());
    return LL_USART_ReceiveData8(this->p_usart);
}

bool Usart::isReadable()
{
    if(LL_USART_IsActiveFlag_RXNE(this->p_usart))   return true;
    return false;
}

bool Usart::isWriteable()
{
    if(LL_USART_IsActiveFlag_TXE(this->p_usart))    return true;
    return false;
}

void Usart::setBaudRate(uint32_t br)
{
    LL_USART_SetBaudRate(this->p_usart, this->p_PeriphClk, LL_USART_OVERSAMPLING_16, br);
}

void Usart::setParity(USART::Parity pr)
{
    LL_USART_SetParity(this->p_usart, (uint32_t)pr);
}

void Usart::setStopBits(USART::StopBits sb)
{
    LL_USART_SetStopBitsLength(this->p_usart, (uint32_t)sb);
}

void Usart::setHardwareFlowControl(USART::HardwareFlowControl hwfc)
{
    LL_USART_SetHWFlowCtrl(this->p_usart, (uint32_t)hwfc);
}

const USART::ConfigStruct *Usart::getConfigStruct()
{
    return &this->p_config;
}

USART_TypeDef * Usart::getUSART()
{
    return this->p_usart;
}
