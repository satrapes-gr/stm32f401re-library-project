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
#include "rccSetup.h"
#include "coreSetup.h"
#include "utils.h"
#include "MockIO.h"
#include <stdio.h>
}

#define MOCK_EXPECTATIONS_SIZE (100)
#define RANDOM_VALUE (0x12345678)

TEST_GROUP(rccSetup)
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

/* TODO: Invert expected and actual values in tests. Expected should come first and actual second */
TEST(rccSetup, TestClockEnableSuccess)
{
    rcc_setup_error_t result;
    ioData virtualRCC_APB1ClockEnableRegister = (ioData) 0x0;

    /* Setup mock expectations */
    /* Read RCC_APB1ClockEnableRegister and enable clock */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
                                 (ioData) virtualRCC_APB1ClockEnableRegister);
    MockIO_Expect_Write((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
                        virtualRCC_APB1ClockEnableRegister | RCC_APB1LPENR_PWRLPEN);
    /* Check that clock was indeed set */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
                                 (ioData) virtualRCC_APB1ClockEnableRegister | RCC_APB1LPENR_PWRLPEN);

    /* Run code */
    result = __enablePowerInterface((ioAddress *) &virtualRCC_APB1ClockEnableRegister);

    /* Check that the clock has been enabled */
    LONGS_EQUAL(RCC_SETUP_SUCCESS, result);
}

TEST(rccSetup, TestClockEnableFailure)
{
    rcc_setup_error_t result;
    ioData virtualRCC_APB1ClockEnableRegister = (ioData) 0x0;

    /* Setup mock expectations */
    /* Read RCC_APB1ClockEnableRegister and enable clock */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
                                 (ioData) virtualRCC_APB1ClockEnableRegister);
    MockIO_Expect_Write((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
                        virtualRCC_APB1ClockEnableRegister | RCC_APB1LPENR_PWRLPEN);
    /* Check that clock was indeed set */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
                                 ((ioData) virtualRCC_APB1ClockEnableRegister & (!RCC_APB1LPENR_PWRLPEN)));

    /* Run code */
    result = __enablePowerInterface((ioAddress *) &virtualRCC_APB1ClockEnableRegister);

    /* Check that the clock has been enabled */
    LONGS_EQUAL(ERROR_POWER_INTERFACE_SETUP_FAILED, result);
}

IGNORE_TEST(rccSetup, WaitUntilHSIReady)
{
    /* Read RCC->CR & RCC_CR_HSIRDY many times until it becomes one */
    uint16_t i;
    rcc_setup_error_t result;
    ioData virtualRCC_APB1ClockEnableRegister = (ioData) 0x0;
    ioData virtualPWR_ControlRegister = (ioData) 0x0;
    ioData virtualRCC_CRRegister = (ioData) 0x0;

    /* Enable power interface mocks*/
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
                                 (ioData) virtualRCC_APB1ClockEnableRegister);
    MockIO_Expect_Write((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
                        virtualRCC_APB1ClockEnableRegister | RCC_APB1LPENR_PWRLPEN);
    /* Check that clock was indeed set */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
                                 (ioData) virtualRCC_APB1ClockEnableRegister | RCC_APB1LPENR_PWRLPEN);

    /* Mock register should return some values of 0 simulating the wait until HSI is ready */
    for (i = 0; i < MOCK_EXPECTATIONS_SIZE - 8; i++)
    {
        MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_CRRegister,
                                     (ioData) virtualRCC_CRRegister & (!RCC_CR_HSIRDY));
    }
    /* Indicate that HSI is ready */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_CRRegister, (ioData) RCC_CR_HSIRDY);
    result = rccSetup((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
            (ioAddress *) &virtualPWR_ControlRegister, (ioAddress *) &virtualRCC_CRRegister,
            RCC_APB1LPENR_PWRLPEN, SCALE_3);
    CHECK_EQUAL(RCC_SETUP_SUCCESS, result);
}

TEST(rccSetup, TestHSIEnableSuccess) {
    rcc_setup_error_t result;
    ioData virtualRCC_CR_Register = (ioData) 0x0;

    /* Setup mock expectations */
    /* Read RCC_APB1ClockEnableRegister and enable clock */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_CR_Register,
                                 (ioData) virtualRCC_CR_Register);
    MockIO_Expect_Write((ioAddress *) &virtualRCC_CR_Register,
            virtualRCC_CR_Register | RCC_CR_HSION);
    /* Check that clock was indeed set */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_CR_Register,
                                 (ioData) virtualRCC_CR_Register | RCC_CR_HSION);

    /* Run code */
    result = __enableHSI((ioAddress *) &virtualRCC_CR_Register);

    /* Check that the clock has been enabled */
    LONGS_EQUAL(RCC_SETUP_SUCCESS, result);
}

TEST(rccSetup, TestHSIEnableFailure) {
    rcc_setup_error_t result;
    ioData virtualRCC_CR_Register = (ioData) 0x0;

    /* Setup mock expectations */
    /* Read RCC_APB1ClockEnableRegister and enable clock */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_CR_Register,
                                 (ioData) virtualRCC_CR_Register);
    MockIO_Expect_Write((ioAddress *) &virtualRCC_CR_Register,
            virtualRCC_CR_Register | RCC_CR_HSION);
    /* Check that clock was indeed set */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_CR_Register,
                                 (ioData) virtualRCC_CR_Register & (!RCC_CR_HSION));

    /* Run code */
    result = __enableHSI((ioAddress *) &virtualRCC_CR_Register);

    /* Check that the clock has been enabled */
    LONGS_EQUAL(ERROR_HSI_ENABLE_FAILED, result);
}
