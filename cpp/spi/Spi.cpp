/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

#include <cstdint>
#include <cstring>
#include "Spi.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_spi.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_rcc.h"

using namespace SPI;

Spi::Spi(SPI_TypeDef * spi, const SPI::ConfigStruct &config) : p_spi(spi)
{
    memcpy(&this->p_config, &config, sizeof(SPI::ConfigStruct));
}

Spi::Spi(const Spi &spi) : Spi(spi.p_spi, spi.p_config) {}

Spi::~Spi()
{
    LL_SPI_Disable(this->p_spi);
    LL_SPI_DeInit(this->p_spi);
}

void Spi::setBaudRate(uint32_t br)
{
    if(this->p_PeriphClk == 0) return;

    uint32_t prescaler, nshifts;
    for(nshifts = 1; nshifts < 8; nshifts++) {
        if (br >= this->p_PeriphClk >> nshifts) break;
    }

    switch(nshifts) {
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

    LL_SPI_SetBaudRatePrescaler(this->p_spi, prescaler);
}

void Spi::setClockPolarity(SPI::ClockPolarity pol)
{
    LL_SPI_SetClockPolarity(this->p_spi, static_cast<uint32_t>(pol));
}

void Spi::setClockPhase(SPI::ClockPhase ph)
{
    LL_SPI_SetClockPhase(this->p_spi, static_cast<uint32_t>(ph));
}

void Spi::setBitOrder(SPI::BitOrder bo)
{
    LL_SPI_SetTransferBitOrder(this->p_spi, static_cast<uint32_t>(bo));
}

const SPI::ConfigStruct *Spi::getConfigStruct()
{
    return static_cast<const SPI::ConfigStruct *>(&this->p_config);
}
SPI_TypeDef *Spi::getSPI()
{
    return this->p_spi;
}
