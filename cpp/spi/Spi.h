/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

#ifndef SPI_H_
#define SPI_H_

#include <cstdint>
#include "IComm.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_spi.h"

namespace SPI {

typedef enum {
    LOW = LL_SPI_POLARITY_LOW,
    HIGH = LL_SPI_POLARITY_HIGH
} ClockPolarity;

typedef enum {
    PHASE_1EDGE = LL_SPI_PHASE_1EDGE,
    PHASE_2EDGE = LL_SPI_PHASE_2EDGE
} ClockPhase;

typedef enum {
    MSB_FIRST = LL_SPI_MSB_FIRST,
    LSB_FIRST = LL_SPI_LSB_FIRST
} BitOrder;

typedef struct {
    uint32_t baudRate;
    ClockPolarity polarity;
    ClockPhase phase;
    BitOrder bitOrder;
} ConfigStruct;

class Spi : public IComm {
public:
    explicit Spi(SPI_TypeDef * spi, const SPI::ConfigStruct &config);
    Spi(const Spi &spi);
    virtual ~Spi();

    void setBaudRate(uint32_t br);
    void setClockPolarity(SPI::ClockPolarity pol);
    void setClockPhase(SPI::ClockPhase ph);
    void setBitOrder(SPI::BitOrder bo);

    const SPI::ConfigStruct *getConfigStruct();
    SPI_TypeDef *getSPI();
    
protected:
    SPI_TypeDef *p_spi;
    SPI::ConfigStruct p_config;
    uint32_t p_PeriphClk;
};

}; // namespace SPI

#endif
