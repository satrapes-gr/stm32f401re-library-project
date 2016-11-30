//#include <stdint.h>
#include "systemSetup.h"

//int global_uninit;
//int global_init = 0;
//static int global_static_uninit;
//static int global_static_init = 0;


void systemSetup(uint32_t * rcc_apb1lpenr_address, uint32_t * pwr_cr_address, uint32_t clock, uint32_t voltage_scaling_output_selection)
{
	*rcc_apb1lpenr_address |= RCC_APB1LPENR_PWRLPEN;
	*pwr_cr_address |= PWR_CR_VOS_1;
}
