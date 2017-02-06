//#include <stdint.h>
#include "systemSetup.h"

//int global_uninit;
//int global_init = 0;
//static int global_static_uninit;
//static int global_static_init = 0;


uint8_t systemSetup(ioAddress *rcc_apb1lpenr_address, ioAddress *pwr_cr_address,
        ioAddress *rcc_cr_address, uint32_t clock, uint32_t voltage_scaling_output_selection)
{
    ioData temporary = 0;
    uint8_t output_flag = 0;
    uint8_t i = 0x1U;;

//    *rcc_apb1lpenr_address |= RCC_APB1LPENR_PWRLPEN;
//    *pwr_cr_address |= PWR_CR_VOS_1;
    temporary = IO_Read(rcc_apb1lpenr_address);
    IO_Write(rcc_apb1lpenr_address, temporary | RCC_APB1LPENR_PWRLPEN);
    if (IO_Read(rcc_apb1lpenr_address) | RCC_APB1LPENR_PWRLPEN) {
        /* Toggle status flag */
        output_flag = output_flag | i;
        i = i << 1;
    }
//    *rcc_apb1lpenr_address = temporary | RCC_APB1LPENR_PWRLPEN;

    temporary = IO_Read(pwr_cr_address);
    IO_Write(pwr_cr_address, temporary | PWR_CR_VOS_1);
    if (IO_Read(pwr_cr_address) | PWR_CR_VOS_1) {
        /* Toggle status flag */
        output_flag = output_flag | i;
        i = i << 1;
    }
    return output_flag;

//
//    /* Wait until HSI ready */
//    do {
//        temporary = IO_Read(rcc_cr_address);
//        temporary = temporary & RCC_CR_HSIRDY;
//    } while (temporary == 0);
}
