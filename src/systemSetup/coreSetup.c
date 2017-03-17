//#include <stdint.h>
#include "coreSetup.h"

core_setup_error_t coreSetup(ioAddress *pwr_cr_address, ioAddress *rcc_cr_address,
                        voltage_scale_t voltage_scaling_output_selection)
{
    core_setup_error_t result;

    /* Select voltage scaling */
    result = __selectVoltageScaling(pwr_cr_address, rcc_cr_address,
                                    voltage_scaling_output_selection);

    return result;
}

core_setup_error_t __selectVoltageScaling(ioAddress *pwr_cr_address, ioAddress *rcc_cr_address,
                                       voltage_scale_t vos)
{
    /* TODO: should there be a check that the address is correct? */
    ioData temp;

    /* Check that PLL is off before proceeding */
    temp = IO_Read(rcc_cr_address);
    if (temp & RCC_CR_PLLON)
    {
        /* Unable to set VOS scale mode as PLL is On */
        return ERROR_VOS_PLL_IS_ON;
    }

    /* Assert PLL is off */
    assert(!(temp & RCC_CR_PLLON));
    /* Check arguments valid modes are 1 (Scale 3 mode) and 2 (Scale 2 mode) */
    if (vos < 1 || vos > 2)
    {
        return ERROR_VOS_INCORRECT_MODE;
    }

    /* Assert valid mode */
    assert((vos == 1) || (vos == 2));

    /* Set VOS mode */
    /* TODO: Verify scaling mode when PLL is turned on */
    /* TODO: Improve bit setting expressions */

    temp = IO_Read(pwr_cr_address);

    IO_Write(pwr_cr_address, (temp | (vos << VOS_BITS_LOCATION)));

    temp = (IO_Read(pwr_cr_address) & PWR_CR_VOS) >> VOS_BITS_LOCATION;
    if (!((temp == 1) && (vos == 1)) || ((temp == 2) && (vos == 2)))
    {
        return ERROR_VOS_SETUP_FAILED;
    } else {
        return CORE_SETUP_SUCCESS;
    }
}
