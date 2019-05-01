/*
* Copyright (c) 2019 Cristóvão Zuppardo Rufino
* See LICENCE file for more information
*/

#ifndef ICOMM_H_
#define ICOMM_H_

#include <cstddef>

class Comm {
public:
    Comm() = default;
    virtual ~Comm() {};

    virtual size_t Write(const void *, size_t s) = 0;
    virtual size_t Read(void *, size_t s) = 0;

    virtual bool isWriteable() = 0;
    virtual bool isReadable() = 0;

};

#endif
