//#include <stdint.h>
#include "systemSetup.h"

//int global_uninit;
//int global_init = 0;
//static int global_static_uninit;
//static int global_static_init = 0;

//static uint8_t select

setup_error_t systemSetup(ioAddress *rcc_apb1lpenr_address, ioAddress *pwr_cr_address,
        ioAddress *rcc_cr_address, uint32_t clock, uint32_t voltage_scaling_output_selection)
{
    setup_error_t result;
//    bool output_flag = true;

//    temporary = IO_Read(rcc_apb1lpenr_address);
//    IO_Write(rcc_apb1lpenr_address, temporary | RCC_APB1LPENR_PWRLPEN);
//    if (IO_Read(rcc_apb1lpenr_address) | RCC_APB1LPENR_PWRLPEN) {
//        /* Toggle status flag */
//        output_flag = output_flag | i;
//        i = i << 1;
//    }
    /* Enable power interface */
    result = enablePowerInterface(rcc_apb1lpenr_address);

    /* Check output and fail early */
    if (result != SYSTEM_SETUP_SUCCESS) {
        return result;
    }
    /* TODO: Figure out how to deal with asserts. Maybe have a DEBUG and a RELEASE build but to do
     *       that I first have to convert my makefiles into eclipse projects. */
    /* Assert result is different than any power interface setup error */
    assert(result != ERROR_POWER_INTERFACE_SETUP_FAILED);

    /* Select voltage scaling */
    result = selectVoltageScaling(pwr_cr_address, rcc_cr_address, SCALE_2);
//    result = IO_Read(pwr_cr_address);
//    IO_Write(pwr_cr_address, result | PWR_CR_VOS_1);
//    if (IO_Read(pwr_cr_address) | PWR_CR_VOS_1) {
//        /* Toggle status flag */
//        output_flag = output_flag | i;
//        i = i << 1;
//    }
//    if (output_flag== true)
//    {
//        return
//    }
    return result;

//bool
//    /* Wait until HSI ready */
//    do {
//        temporary = IO_Read(rcc_cr_address);
//        temporary = temporary & RCC_CR_HSIRDY;
//    } while (temporary == 0);
}

setup_error_t enablePowerInterface(ioAddress *rcc_apb1lpenr_address)
{
    ioData temporary;

    temporary = IO_Read(rcc_apb1lpenr_address);
    IO_Write(rcc_apb1lpenr_address, temporary | RCC_APB1LPENR_PWRLPEN);
    /*TODO: potential bug in the OR this can be non zero if any other bit than the one currently
     *      examined is non zero
     */
    if (!(IO_Read(rcc_apb1lpenr_address) & RCC_APB1LPENR_PWRLPEN))
    {
        return ERROR_POWER_INTERFACE_SETUP_FAILED;
    } else {
        return SYSTEM_SETUP_SUCCESS;
    }
}

setup_error_t selectVoltageScaling(ioAddress *pwr_cr_address, ioAddress *rcc_cr_address,
                                   voltage_scale_t vos)
{
    /* TODO: check that value is correct invalid vos */
    /* TODO: check that pll is off */
    /* TODO: should there be a check that the address is correct? */
    ioData temp;

    /* Check that PLL is off before proceeding */
    temp = IO_Read(rcc_cr_address);
    if (!(temp & RCC_CR_PLLON))
    {
        /* Unable to set VOS scale mode as PLL is On */
        return ERROR_VOS_PLL_IS_ON;
    }

    /* Assert PLL is off */
    assert(!(temp & RCC_CR_PLLON));

    /* Check arguments valid modes are 1 (Scale 3 mode) and 2 (Scale 2 mode) */
    if (vos < 1 || vos > 2)
    {
        return ERROR_VOS_WRONG_MODE;
    }

    /* Assert valid mode */
    assert((vos == 1) || (vos == 2));

    /* Set VOS mode */
    /* TODO: Verify scaling mode when PLL is turned on */
    /* TODO: Improve bit setting expressions */
    temp = IO_Read(pwr_cr_address);
    IO_Write(pwr_cr_address, (temp | (vos << 14)));
    temp = (IO_Read(pwr_cr_address) & PWR_CR_VOS) >> 14;
    if (!((temp == 1) && (vos == 1)) || ((temp == 2) && (vos == 2)))
    {
        return ERROR_VOS_SETUP_FAILED;
    } else {
        return SYSTEM_SETUP_SUCCESS;
    }
}
