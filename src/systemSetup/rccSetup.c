//#include <stdint.h>
#include "rccSetup.h"

//int global_uninit;
//int global_init = 0;
//static int global_static_uninit;
//static int global_static_init = 0;

//static uint8_t select

rcc_setup_error_t rccSetup(ioAddress *rcc_apb1lpenr_address, ioAddress *pwr_cr_address,
        ioAddress *rcc_cr_address, ioAddress *rcc_cfgr_address, uint32_t clock,
        uint32_t voltage_scaling_output_selection)
{
    rcc_setup_error_t result;
    /* TODO: Add a function pointer vector where all these functions are going to be in and then we
     *       will iterate over them without repeating the CHECK_OUTPUT(result, RCC_SETUP_SUCCESS);
     *       macro all the time.
     */
    /* Reset RCC clock configuration to the default reset state */
    /* Enable internal clock (HSI) */
    result = __enableHSI(rcc_cr_address);
    CHECK_OUTPUT(result, RCC_SETUP_SUCCESS);

    /* Reset RCC_CFGR */
    result = __resetCFGRReg(rcc_cfgr_address);
    CHECK_OUTPUT(result, RCC_SETUP_SUCCESS);

    /* TODO: Check if it best to set multiple bits at the same time with one function. At least
     *       consider this */
    /* Disable HSE */
    result = __disableHSE(rcc_cr_address);
    CHECK_OUTPUT(result, RCC_SETUP_SUCCESS);

    /* Disable CSS */
    result = __disableCSS(rcc_cr_address);
    CHECK_OUTPUT(result, RCC_SETUP_SUCCESS);

    /* Disable PLL */
    result = __disablePLL(rcc_cr_address);
    CHECK_OUTPUT(result, RCC_SETUP_SUCCESS);

    /* Enable power interface */
    result = __enablePowerInterface(rcc_apb1lpenr_address);

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
    ENABLE_BITS_AND_CHECK_RETURN_ERROR(rcc_apb1lpenr_address, RCC_APB1LPENR_PWRLPEN,
                                ERROR_POWER_INTERFACE_SETUP_FAILED, RCC_SETUP_SUCCESS);
    /*TODO: potential bug in the OR this can be non zero if any other bit than the one currently
     *      examined is non zero */
}

rcc_setup_error_t __enableHSI(ioAddress *rcc_cr_address)
{
    /* TODO: add disable HSI for symmetry */
    ENABLE_BITS_AND_CHECK_RETURN_ERROR(rcc_cr_address, RCC_CR_HSION, ERROR_HSI_ENABLE_FAILED,
                                       RCC_SETUP_SUCCESS);
}

rcc_setup_error_t __resetCFGRReg(ioAddress *rcc_cfgr_address)
{
    IO_Write(rcc_cfgr_address, RCC_CFGR_RESET_VALUE);
    if (IO_Read(rcc_cfgr_address))
    {
        return ERROR_RESET_CFGR;
    } else
    {
        return RCC_SETUP_SUCCESS;
    }
}

rcc_setup_error_t __disableHSE(ioAddress *rcc_cr_address)
{
    /* TODO: add enable HSE for symmetry */
    DISABLE_BITS_AND_CHECK_RETURN_ERROR(rcc_cr_address, RCC_CR_HSEON, ERROR_HSE_DISABLE_FAILED,
                                        RCC_SETUP_SUCCESS);
}

rcc_setup_error_t __disableCSS(ioAddress *rcc_cr_address)
{
    /* TODO: add enable HSE for symmetry */
    DISABLE_BITS_AND_CHECK_RETURN_ERROR(rcc_cr_address, RCC_CR_CSSON, ERROR_CSS_DISABLE_FAILED,
                                        RCC_SETUP_SUCCESS);
}

rcc_setup_error_t __disablePLL(ioAddress *rcc_cr_address)
{
    /* TODO: add enable HSE for symmetry */
    DISABLE_BITS_AND_CHECK_RETURN_ERROR(rcc_cr_address, RCC_CR_PLLON, ERROR_PLL_DISABLE_FAILED,
                                        RCC_SETUP_SUCCESS);
}

rcc_setup_error_t __selectPLLQ(ioAddress *rcc_pllcfgr_address, uint8_t PLLQ_value)
{

}

rcc_setup_error_t __resetPLLCFGR(ioAddress *rcc_pllcfgr_address)
{
    return RCC_SETUP_SUCCESS;
}
