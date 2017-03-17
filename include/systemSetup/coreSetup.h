#ifndef CORE_SETUP_H
#define CORE_SETUP_H
#include "stm32f4xx.h"
#include "IO.h"

#include <stdbool.h>
#include <assert.h>


#define VOS_BITS_LOCATION (14)

/*
 * Possible errors on core setup
 */
typedef enum {
                CORE_SETUP_SUCCESS = 0,
                ERROR_VOS_PLL_IS_ON,
                ERROR_VOS_INCORRECT_MODE,
                ERROR_VOS_SETUP_FAILED,
             } core_setup_error_t;

/*
* Voltage scaler allowed values
*/
typedef enum {
                SCALE_2 = 2,
                SCALE_3 = 1,
} voltage_scale_t;

/**
 * @brief This function is used to setup anything related to the core
 * @param pwr_cr_address Address of power control register
 * @param rcc_cr_address Address of reset and clock control register
 * @param voltage_scaling_output_selection Mode of voltage scaling (0 - 3) 1 is scale 3 and 2 is
 *                                         scale 2 the other two modes are reserved.
 * @return Type of setup error
 *
 * TODO: Add more detailed description
 */
core_setup_error_t coreSetup(ioAddress *pwr_cr_address, ioAddress *rcc_cr_address,
                        voltage_scale_t voltage_scaling_output_selection);

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
core_setup_error_t __selectVoltageScaling(ioAddress *pwr_cr_address, ioAddress *rcc_cr_address,
                                   voltage_scale_t vos);

#endif /* CORE_SETUP_H */
