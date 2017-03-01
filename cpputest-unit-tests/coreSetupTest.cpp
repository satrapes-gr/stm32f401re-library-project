//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved         
//-    For use by owners of Test-Driven Development for Embedded C,   
//-    and attendees of Renaissance Software Consulting, Co. training 
//-    classes.                                                       
//-                                                                   
//-    Available at http://pragprog.com/titles/jgade/                 
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3               
//-                                                                   
//-    Authorized users may use this source code in your own          
//-    projects, however the source code may not be used to           
//-    create training material, courses, books, articles, and        
//-    the like. We make no guarantees that this source code is       
//-    fit for any purpose.                                           
//-                                                                   
//-    www.renaissancesoftware.net james@renaissancesoftware.net      
//- ------------------------------------------------------------------

#include "CppUTest/TestHarness.h"
#include "CppUTest/TestOutput.h"

extern "C"
{
#include "coreSetup.h"
#include "MockIO.h"
#include <stdio.h>
}

#define MOCK_EXPECTATIONS_SIZE (100)
#define RANDOM_VALUE (0x12345678)
#define INCORRECT_VOS_VALUE (0x0000C000)
#define INVALID_VOS_MODE (3)

TEST_GROUP(coreSetup)
{
    void setup()
    {
        MockIO_Create(MOCK_EXPECTATIONS_SIZE);
    }

    void teardown()
    {
        MockIO_Verify_Complete();
        MockIO_Destroy();
    }
};

/*
 * This test will call selectVoltageScaling function and fail because the PLL is On when we try to
 * modify the contents of the VOS bits.
 */
TEST(coreSetup, TestSetRegulatorPLLIsOn)
{
    core_setup_error_t result;
    ioData virtualPWR_ControlRegister = (ioData) 0x0;
    ioData virtualRCC_CRRegister = (ioData) RCC_CR_PLLON;   /* Random value with PLL On */

    /* Setup mock expectations */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_CRRegister,
                                 (ioData) virtualRCC_CRRegister);

    /* Run code */
    result = __selectVoltageScaling((ioAddress *) &virtualPWR_ControlRegister,
                                  (ioAddress *) &virtualRCC_CRRegister, (voltage_scale_t) SCALE_2);

    CHECK_EQUAL(result, ERROR_VOS_PLL_IS_ON);
}

/*
 * This test will call selectVoltageScaling function and fail because the VOS scale mode is going to
 * be incorrect..
 */
TEST(coreSetup, TestSetRegulatorInvalidVOSMode)
{
    core_setup_error_t result;
    ioData virtualPWR_ControlRegister = (ioData) 0x0;
    ioData virtualRCC_CRRegister = (ioData) 0xB;    /* Random value with PLL off */

    /* Setup mock expectations */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_CRRegister,
                                 (ioData) virtualRCC_CRRegister);

    /* Run code */
    result = __selectVoltageScaling((ioAddress *) &virtualPWR_ControlRegister,
                                  (ioAddress *) &virtualRCC_CRRegister,
                                  (voltage_scale_t) INVALID_VOS_MODE);

    CHECK_EQUAL(result, ERROR_VOS_INCORRECT_MODE);
}

/*
 * This test will call selectVoltageScaling function and check that it was written correctly. It
 * will then return a successful status code.
 */
TEST(coreSetup, TestSetRegulatorValidVOSModeCorrectlyWritten)
{
    core_setup_error_t result;
    voltage_scale_t vos = SCALE_3;
    ioData virtualPWR_ControlRegister = (ioData) 0x0;
    ioData virtualRCC_CRRegister = (ioData) 0xB;    /* Random value with PLL off */

    /* Setup mock expectations */
    /* PLL is Off */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_CRRegister,
                                 (ioData) virtualRCC_CRRegister);

    /* Set vos value in pwr_cr register */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualPWR_ControlRegister,
                                 (ioData) virtualPWR_ControlRegister);

    MockIO_Expect_Write((ioAddress *) &virtualPWR_ControlRegister,
                        (ioData) virtualPWR_ControlRegister | (vos << VOS_BITS_LOCATION));

    /* Check it actually set the correct value */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualPWR_ControlRegister,
                                 (ioData) virtualPWR_ControlRegister | (vos << VOS_BITS_LOCATION));

    /* Run code */
    result = __selectVoltageScaling((ioAddress *) &virtualPWR_ControlRegister,
                                  (ioAddress *) &virtualRCC_CRRegister, vos);

    CHECK_EQUAL(result, CORE_SETUP_SUCCESS);
}

/*
 * This test will call selectVoltageScaling function and check that it was written incorrectly. It
 * will then return the appropriate error code.
 */
TEST(coreSetup, TestSetRegulatorValidVOSModeIncorrectlyWritten)
{
    core_setup_error_t result;
    voltage_scale_t vos = SCALE_3;
    ioData virtualPWR_ControlRegister = (ioData) 0x0;
    ioData virtualRCC_CRRegister = (ioData) 0xB;    /* Random value with PLL off */

    /* Setup mock expectations */
    /* PLL is Off */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_CRRegister,
                                 (ioData) virtualRCC_CRRegister);

    /* Set vos value in pwr_cr register */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualPWR_ControlRegister,
                                 (ioData) virtualPWR_ControlRegister);

    MockIO_Expect_Write((ioAddress *) &virtualPWR_ControlRegister,
                        (ioData) virtualPWR_ControlRegister | (vos << VOS_BITS_LOCATION));

    /* Check it actually set an incorrect value 0 for incorrect.*/
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualPWR_ControlRegister,
                                 (ioData) INCORRECT_VOS_VALUE);

    /* Run code */
    result = __selectVoltageScaling((ioAddress *) &virtualPWR_ControlRegister,
                                  (ioAddress *) &virtualRCC_CRRegister, vos);

    CHECK_EQUAL(result, ERROR_VOS_SETUP_FAILED);
}
