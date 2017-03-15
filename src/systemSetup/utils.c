//#include <stdint.h>
#include "utils.h"

/* TODO: Unittest __setBitMask functions */
bool __setBitMask(ioAddress *reg_address, uint32_t bit_mask)
{
    ioData temporary;

    temporary = IO_Read(reg_address);
    IO_Write(reg_address, temporary | bit_mask);

    /* TODO: Fix this. if one bit fails this will still succeed. For the time being assume that
     *       they all failed */
    return (bool) (!(IO_Read(reg_address) & bit_mask));
}

/* TODO: Unittest __clearBitMask functions */
bool __clearBitMask(ioAddress *reg_address, uint32_t bit_mask)
{
    ioData temporary;

    temporary = IO_Read(reg_address);
    IO_Write(reg_address, temporary & (~bit_mask));

    return (bool) (IO_Read(reg_address) & bit_mask);
}
