/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

#include <cstdint>
#include "SpiMaster.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_spi.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_rcc.h"

using namespace SPI;

SpiMaster::SpiMaster(SPI_TypeDef *spi, const SPI::ConfigStruct &config) : Spi(spi, config)
{
    LL_RCC_ClocksTypeDef rcc_clocks;
    LL_RCC_GetSystemClocksFreq(&rcc_clocks);

#if defined(SPI1)
    if (this->p_spi == SPI1) {
        this->p_PeriphClk = rcc_clocks.PCLK2_Frequency;
    }
#endif /* SPI1 */
#if defined(SPI2)
    if (this->p_spi == SPI2) {
        this->p_PeriphClk = rcc_clocks.PCLK1_Frequency;
    }
#endif /* SPI2 */
#if defined(SPI3)
    if (this->p_spi == SPI3) {
        this->p_PeriphClk = rcc_clocks.PCLK1_Frequency;
    }
#endif /* SPI3 */
#if defined(SPI4)
    if (this->p_spi == SPI4) {
        this->p_PeriphClk = rcc_clocks.PCLK2_Frequency;
    }
#endif /* SPI4 */
#if defined(SPI5)
    if (this->p_spi == SPI5) {
        this->p_PeriphClk = rcc_clocks.PCLK2_Frequency;
    }
#endif /* SPI5 */
#if defined(SPI6)
    if (this->p_spi == SPI6) {
        this->p_PeriphClk = rcc_clocks.PCLK2_Frequency;
    }
#endif /* SPI6 */

    uint32_t prescaler, nshifts;
    for(nshifts = 1; nshifts < 8; nshifts++) {
        if (this->p_config.baudRate <= this->p_PeriphClk >> nshifts) break;
    }

    switch(nshifts){
        case 1: prescaler = LL_SPI_BAUDRATEPRESCALER_DIV2; break;
        case 2: prescaler = LL_SPI_BAUDRATEPRESCALER_DIV4; break;
        case 3: prescaler = LL_SPI_BAUDRATEPRESCALER_DIV8; break;
        case 4: prescaler = LL_SPI_BAUDRATEPRESCALER_DIV16; break;
        case 5: prescaler = LL_SPI_BAUDRATEPRESCALER_DIV32; break;
        case 6: prescaler = LL_SPI_BAUDRATEPRESCALER_DIV64; break;
        case 7: prescaler = LL_SPI_BAUDRATEPRESCALER_DIV128; break;
        case 8: prescaler = LL_SPI_BAUDRATEPRESCALER_DIV256; break;
        default: prescaler = LL_SPI_BAUDRATEPRESCALER_DIV2; break;
    }

    LL_SPI_InitTypeDef initstruct = {
        .TransferDirection = LL_SPI_FULL_DUPLEX,
        .Mode              = LL_SPI_MODE_MASTER,
        .DataWidth         = LL_SPI_DATAWIDTH_8BIT,
        .ClockPolarity     = this->p_config.polarity,
        .ClockPhase        = this->p_config.phase,
        .NSS               = LL_SPI_NSS_SOFT,
        .BaudRate          = prescaler,
        .BitOrder          = this->p_config.bitOrder,
        .CRCCalculation    = LL_SPI_CRCCALCULATION_DISABLE,
        .CRCPoly           = 7U
    };

    LL_SPI_Init(this->p_spi, &initstruct);
    LL_SPI_Enable(this->p_spi);
}

SpiMaster::SpiMaster(const SpiMaster &spi) : SpiMaster(spi.p_spi, spi.p_config) {}

SpiMaster::~SpiMaster() {}

size_t SpiMaster::Write(const void *data, size_t s)
{
    const uint8_t *udata = static_cast<const uint8_t *>(data);
    size_t i;
    for(i = 0; i < s; i++) {
        Write(udata[i]);
    }

    return i;
}

size_t SpiMaster::Read(void *data, size_t s)
{
    uint8_t *udata = static_cast<uint8_t *>(data);
    size_t i;
    for(i = 0; i < s; i++) {
        udata[i] = Read();
    }

    return i;
}

void SpiMaster::Write(uint8_t c)
{
    while(!isWriteable());
    LL_SPI_TransmitData8(this->p_spi, c);
}

uint8_t SpiMaster::Read()
{
    while(!isReadable());
    return LL_SPI_ReceiveData8(this->p_spi);
}

bool SpiMaster::isWriteable()
{
    if(LL_SPI_IsActiveFlag_TXE(this->p_spi))   return true;
    return false;
}

bool SpiMaster::isReadable()
{
    if(LL_SPI_IsActiveFlag_RXNE(this->p_spi))   return true;
    return false;
}