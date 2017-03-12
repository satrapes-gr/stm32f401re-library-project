//#include <stdint.h>
#include "rccSetup.h"

//int global_uninit;
//int global_init = 0;
//static int global_static_uninit;
//static int global_static_init = 0;

//static uint8_t select

rcc_setup_error_t rccSetup(ioAddress *rcc_apb1lpenr_address, ioAddress *pwr_cr_address,
        ioAddress *rcc_cr_address, uint32_t clock, uint32_t voltage_scaling_output_selection)
{
    rcc_setup_error_t result;

    /* Reset RCC clock configuration to the default reset state */
    /* Enable internal clock (HSI) */
    result = __enableHSI(rcc_cr_address);

    /* Enable power interface */
    result = __enablePowerInterface(rcc_apb1lpenr_address);

    /* Check output and fail early */
    if (result != RCC_SETUP_SUCCESS) {
        return result;
    }
    /* TODO: Figure out how to deal with asserts. Maybe have a DEBUG and a RELEASE build but to do
     *       that I first have to convert my makefiles into eclipse projects. */
    /* Assert result is different than any power interface setup error */
    assert(result != ERROR_POWER_INTERFACE_SETUP_FAILED);

    /* Wait until HSI is ready */
    while ((IO_Read(rcc_cr_address) & RCC_CR_HSIRDY) == 0);

    /* TODO: Adding an assert that uses an IO_Read would mess the code so not sure what to do */
    return result;
}

rcc_setup_error_t __enablePowerInterface(ioAddress *rcc_apb1lpenr_address)
{
    /* TODO: I should add a clock variable it is already in the rccSetup */
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
        return RCC_SETUP_SUCCESS;
    }
}

rcc_setup_error_t __enableHSI(ioAddress *rcc_cr_address) {
    /* TODO: add disable HSI for symmetry */
    ioData temporary;

    temporary = IO_Read(rcc_cr_address);
    IO_Write(rcc_cr_address, temporary | RCC_CR_HSION);

    if (!(IO_Read(rcc_cr_address) & RCC_CR_HSION)) {
        return ERROR_HSI_ENABLE_FAILED;
    } else {
        return RCC_SETUP_SUCCESS;
    }
}
