#ifndef ICOMM_H_
#define ICOMM_H_

#include <cstddef>
#include <array>

namespace COMM {

class Comm {

    virtual ~Comm() {};

    virtual size_t WriteData(const void *, size_t s) = 0;
    virtual size_t ReadData(void *, size_t s) = 0;

};

}; // namespace COMM

#endif
