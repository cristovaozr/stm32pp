/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

#ifndef ICOMM_H_
#define ICOMM_H_

#include <cstddef>

class IComm {
public:
    IComm() = default;
    virtual ~IComm() {};

    virtual size_t Write(const void *, size_t s) = 0;
    virtual size_t Read(void *, size_t s) = 0;
    
    virtual void Write(uint8_t c) = 0;
    virtual uint8_t Read() = 0;

    virtual bool isWriteable() = 0;
    virtual bool isReadable() = 0;

};

#endif
