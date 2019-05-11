/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

#ifndef SPIMASTER_H_
#define SPIMASTER_H_

#include <cstdint>
#include "Spi.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_spi.h"

namespace SPI {

class SpiMaster : public Spi {

public:
    explicit SpiMaster(SPI_TypeDef *spi, const ConfigStruct &config);
    SpiMaster(const SpiMaster &spi);
    virtual ~SpiMaster();

    virtual size_t Write(const void *, size_t s);
    virtual size_t Read(void *, size_t s);
    
    virtual void Write(uint8_t c);
    virtual uint8_t Read();

    virtual bool isWriteable();
    virtual bool isReadable();

};

}; // namespace SPI

#endif