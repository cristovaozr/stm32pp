#include "Core.h"
#include <stm32f407xx.h>
#include <cmsis_gcc.h>

using namespace CORE;

void DisableInterrupts()
{
    __disable_irq();
}

void EnableInterrupts()
{
    __enable_irq();
}