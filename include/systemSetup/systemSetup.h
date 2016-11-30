#ifndef SYSTEMSETUP_H
#define SYSTEMSETUP_H
#include "stm32f4xx.h"

void systemSetup(uint32_t * rcc_apb1lpenr_address, uint32_t * pwr_cr_address, uint32_t clock, uint32_t voltage_scaling_output_selection);

#endif /* SYSTEMSETUP_H */
