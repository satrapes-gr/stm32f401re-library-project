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
#include "systemSetup.h"
#include "MockIO.h"
#include<stdio.h>
}

#define MOCK_EXPECTATIONS_SIZE (100)
#define RANDOM_VALUE (0x12345678)

TEST_GROUP(systemSetup)
{
    void setup()
    {
        MockIO_Create(MOCK_EXPECTATIONS_SIZE);;
    }

    void teardown()
    {
        MockIO_Verify_Complete();
        MockIO_Destroy();
    }
};

TEST(systemSetup, TestClockEnableSuccess)
{
    setup_error_t result;
    ioData virtualRCC_APB1ClockEnableRegister = (ioData) 0x0;
//    ioData virtualPWR_ControlRegister = (ioData) 0x0;
//    ioData virtualRCC_CRRegister = (ioData) 0x0;

    /* Setup mock expectations */
    /* Read RCC_APB1ClockEnableRegister and enable clock */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
                                 (ioData) virtualRCC_APB1ClockEnableRegister);
    MockIO_Expect_Write((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
                        virtualRCC_APB1ClockEnableRegister | RCC_APB1LPENR_PWRLPEN);
    /* Check that clock was indeed set */
    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
                                 (ioData) virtualRCC_APB1ClockEnableRegister | RCC_APB1LPENR_PWRLPEN);

//    /* Read PWR_ControlRegister and enable power */
//    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualPWR_ControlRegister,
//                                 (ioData) virtualPWR_ControlRegister);
//    MockIO_Expect_Write((ioAddress *) &virtualPWR_ControlRegister,
//                         virtualPWR_ControlRegister | PWR_CR_VOS_1);
//    /* Check that the power was enabled */
//    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualPWR_ControlRegister,
//                                 (ioData) virtualPWR_ControlRegister | PWR_CR_VOS_1);

//    /* Read RCC_APB1ClockEnableRegister to verify that the clock has been enabled */
//    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
//                        virtualRCC_APB1ClockEnableRegister | RCC_APB1LPENR_PWRLPEN);

    /* Run code */
//    result = systemSetup((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
//            (ioAddress *) &virtualPWR_ControlRegister, (ioAddress *) &virtualRCC_CRRegister,
//            RCC_APB1LPENR_PWRLPEN, PWR_CR_VOS_1);
    result = enablePowerInterface((ioAddress *) &virtualRCC_APB1ClockEnableRegister);

    /* Check that the clock has been enabled */
    LONGS_EQUAL(result, SYSTEM_SETUP_SUCCESS);
}

TEST(systemSetup, TestClockEnableFailure)
{
    setup_error_t result;
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

    result = enablePowerInterface((ioAddress *) &virtualRCC_APB1ClockEnableRegister);

    /* Check that the clock has been enabled */
    LONGS_EQUAL(result, ERROR_POWER_INTERFACE_SETUP_FAILED);
}

//TEST(systemSetup, TestSetRegulatorVoltageScale)
//{
//    ioData virtualRCC_APB1ClockEnableRegister = (ioData) 0xF;
//    ioData virtualPWR_ControlRegister = (ioData) 0xA;
//    ioData virtualRCC_CRRegister = (ioData) 0xB;
//
//    /* Setup mock expectations */
//    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
//                                 (ioData) virtualRCC_APB1ClockEnableRegister);
//    MockIO_Expect_Write((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
//                        virtualRCC_APB1ClockEnableRegister | RCC_APB1LPENR_PWRLPEN);
//
//    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualPWR_ControlRegister,
//                                 (ioData) virtualPWR_ControlRegister);
//    MockIO_Expect_Write((ioAddress *) &virtualPWR_ControlRegister,
//                         virtualPWR_ControlRegister | PWR_CR_VOS_1);
//    printf("before\n");
//    printf("virtualRCC_APB1ClockEnableRegister= %d\nvirtualPWR_ControlRegister=%d\nvirtualRCC_CRRegister= %d\n",
//            (int) virtualRCC_APB1ClockEnableRegister, (int) virtualPWR_ControlRegister,
//            (int) virtualRCC_CRRegister);
//    systemSetup((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
//            (ioAddress *) &virtualPWR_ControlRegister, (ioAddress *) &virtualRCC_CRRegister,
//            RCC_APB1LPENR_PWRLPEN, PWR_CR_VOS_1);
//    printf("after\n");
//    printf("virtualRCC_APB1ClockEnableRegister= %d\nvirtualPWR_ControlRegister=%d\nvirtualRCC_CRRegister= %d\n",
//            (int) virtualRCC_APB1ClockEnableRegister, (int) virtualPWR_ControlRegister,
//            (int) virtualRCC_CRRegister);
//    CHECK_EQUAL(virtualPWR_ControlRegister, 0x00008000);
//}

//TEST(systemSetup, WaitUntilHSIReady)
//{
//    /* Read RCC->CR & RCC_CR_HSIRDY many times until it becomes one */
//    uint16_t i;
//    ioData virtualPWR_ControlRegister = (ioData) 0x0;
//    ioData virtualRCC_APB1ClockEnableRegister = (ioData) 0x0;
//    ioData virtualRCC_CRRegister = (ioData) 0x0;;
//
//    /* Mock register should return some values of 0 simulating the wait until HSI is ready */
//    for (i = 0; i < MOCK_EXPECTATIONS_SIZE - 1; i++)
//    {
//        MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_CRRegister, (ioData) 0xFFFFFFFF & 0xFFFFFFFD);
//    }
//    /* Indicate that HSI is ready */
//    MockIO_Expect_ReadThenReturn((ioAddress *) &virtualRCC_CRRegister, (ioData) 0xFFFFFFFD | 0x02);
//    systemSetup((ioAddress *) &virtualRCC_APB1ClockEnableRegister,
//            (ioAddress *) &virtualPWR_ControlRegister, (ioAddress *) &virtualRCC_CRRegister,
//            RCC_APB1LPENR_PWRLPEN, PWR_CR_VOS_1);
//    MockIO_Verify_Complete();
//    CHECK_TRUE(1 == 0);
//}

