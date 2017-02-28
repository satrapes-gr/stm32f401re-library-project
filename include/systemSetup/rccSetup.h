#ifndef RCCSETUP_H
#define RCCSETUP_H
#include "stm32f4xx.h"
#include "IO.h"

#include <stdbool.h>
#include <assert.h>

#define VOS_BITS_LOCATION (14)

typedef enum {
                RCC_SETUP_SUCCESS = 0,
                ERROR_POWER_INTERFACE_SETUP_FAILED,
                ERROR_VOS_PLL_IS_ON,
                ERROR_VOS_INCORRECT_MODE,
                ERROR_VOS_SETUP_FAILED,
             } setup_error_t;

typedef enum {
                SCALE_2 = 2,
                SCALE_3 = 1,
} voltage_scale_t;

setup_error_t rccSetup(ioAddress *rcc_apb1lpenr_address, ioAddress *pwr_cr_address,
        ioAddress *rcc_cr_address, uint32_t clock, uint32_t voltage_scaling_output_selection);

/**
 * @brief This function is used to enable the power interface
 * @param rcc_apb1lpenr_address
 * @return A type of error during setup
 */
setup_error_t __enablePowerInterface(ioAddress *rcc_apb1lpenr_address);
/* TODO: potentially add a disablePowerInterface function here for symmetry */

/**
 * @brief This function is used to select the voltage scaling of the main internal voltage regulator
 * @param pwr_cr_address Address of power control register
 * @param vos Mode of voltage scaling (0 - 3) 1 is scale 3 and 2 is scale 2 the other two modes are
 *            reserved.
 * @return Type of setup error
 *
 * The new value is going to take effect when we will turn the PLL On. When the PLL is off the
 * voltage regulator is set to scale 3 independently of the VOS register content. The voltage
 * regulator controls output voltage to achieve a tradeoff between performance and power consumption
 * when the device does not operate at the maximum frequency.
 */
/* TODO: Check what scale 2 and scale 3 mean */
setup_error_t __selectVoltageScaling(ioAddress *pwr_cr_address, ioAddress *rcc_cr_address,
                                   voltage_scale_t vos);
#endif /* RCCSETUP_H */
