#include <stdint.h>
#include "UARTDriver.h"

void UARTDriver_Create(uint32_t * RCC_APB1ENR)
{
    *RCC_APB1ENR = 0;
}
