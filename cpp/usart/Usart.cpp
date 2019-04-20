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
        LL_GPIO_Init(GPIOA, &initstruct);

    }
    else if (this->p_usart == USART2) {
        this->p_PeriphClk = rcc_clocks.PCLK1_Frequency;
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

    }
#if defined(USART3)
    else if (this->p_usart == USART3) {
        this->p_PeriphClk = rcc_clocks.PCLK1_Frequency;
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
    }
#endif /* USART3 */
#if defined(USART6)
    else if (this->p_usart == USART6) {
        this->p_PeriphClk = rcc_clocks.PCLK2_Frequency;
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6);
    }
#endif /* USART6 */
#if defined(UART4)
    else if (this->p_usart == UART4) {
        this->p_PeriphClk = rcc_clocks.PCLK1_Frequency;
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
    }
#endif /* UART4 */
#if defined(UART5)
    else if (this->p_usart == UART5) {
        this->p_PeriphClk = rcc_clocks.PCLK1_Frequency;
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
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

void Usart::Write(uint8_t c)
{
    LL_USART_TransmitData8(this->p_usart, c);
}

uint32_t Usart::Write(const void *data, uint32_t size)
{
    uint32_t i;
    const uint8_t *udata = (const uint8_t *)data;

    for(i = 0; i < size; i++) {
        while(!isWriteable());
        Write(udata[i]);
    }

    return i;
}

uint8_t Usart::Read()
{
    return LL_USART_ReceiveData8(this->p_usart);
}

uint32_t Usart::Read(void *data, uint32_t size)
{
    uint32_t i;
    uint8_t *udata = (uint8_t *)data;

    for(i = 0; i < size; i++) {
        while(!isReadable());
        udata[i] = Read();
    }

    return i;
}

bool Usart::isReadable()
{
    bool ret = false;
    
    if(LL_USART_IsActiveFlag_RXNE(this->p_usart))   ret = true;
    return ret;
}

bool Usart::isWriteable()
{
    bool ret = false;
    
    if(LL_USART_IsActiveFlag_TXE(this->p_usart))    ret = true;
    return ret;
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
