#ifndef SYSTEMSETUP_H
#define SYSTEMSETUP_H
#include "stm32f4xx.h"
#include "IO.h"

uint8_t systemSetup(ioAddress *rcc_apb1lpenr_address, ioAddress *pwr_cr_address,
        ioAddress *rcc_cr_address, uint32_t clock, uint32_t voltage_scaling_output_selection);

#endif /* SYSTEMSETUP_H */
