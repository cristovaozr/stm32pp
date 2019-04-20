#ifndef USART_H_
#define USART_H_

#include <cstdint>
#include "stm32f4xx.h"
#include "stm32f4xx_ll_usart.h"

namespace USART {

typedef enum {
    NONE = LL_USART_PARITY_NONE,
    ODD = LL_USART_PARITY_ODD,
    EVEN = LL_USART_PARITY_EVEN
} Parity;

typedef enum {
    ONE = LL_USART_STOPBITS_1,
    TWO = LL_USART_STOPBITS_2
} StopBits;

typedef enum {
    HW_NONE = LL_USART_HWCONTROL_NONE,
    HW_RTSCTS = LL_USART_HWCONTROL_RTS_CTS
} HardwareFlowControl;

typedef struct {
    uint32_t Baudrate;
    USART::Parity Parity;
    USART::StopBits StopBits;
    USART::HardwareFlowControl HardwareFlowControl;
} ConfigStruct;

class Usart {
public:

    explicit Usart(USART_TypeDef *usart, const USART::ConfigStruct &config);
    Usart(const Usart &c);
    virtual ~Usart();

    virtual void Write(uint8_t c);
    virtual uint32_t Write(const void *data, uint32_t size);

    virtual uint8_t Read();
    virtual uint32_t Read(void *data, uint32_t size);

    virtual bool isReadable();
    virtual bool isWriteable();

    void setBaudRate(uint32_t br);
    void setParity(USART::Parity pr);
    void setStopBits(USART::StopBits sb);
    void setHardwareFlowControl(USART::HardwareFlowControl hwfc);

    const USART::ConfigStruct *getConfigStruct();
    USART_TypeDef *getUSART();
protected:
    USART_TypeDef *p_usart;
    USART::ConfigStruct p_config;
    uint32_t p_PeriphClk;
    // TODO: add something to acknowledge interruptions
};

}; // namespace USART
#endif
