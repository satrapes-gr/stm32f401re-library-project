//#include <stdint.h>
#include "utils.h"

bool __setBitMask(ioAddress *reg_address, uint32_t bit_mask) {
    ioData temporary;

    temporary = IO_Read(reg_address);
    IO_Write(reg_address, temporary | bit_mask);

    return (bool) (!(IO_Read(reg_address) & bit_mask));
}
