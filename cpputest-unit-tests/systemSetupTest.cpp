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
}

TEST_GROUP(systemSetup)
{
    void setup()
    {
        ;
    }

    void teardown()
    {
        ;
    }
};

TEST(systemSetup, TestClockEnable)
{
    uint32_t virtualRCC_APB1ClockEnableRegister = 0x0;
    uint32_t virtualPWR_ControlRegister = 0x0;
    systemSetup(&virtualRCC_APB1ClockEnableRegister, &virtualPWR_ControlRegister, RCC_APB1LPENR_PWRLPEN, PWR_CR_VOS_1);
    CHECK_EQUAL(virtualRCC_APB1ClockEnableRegister, 0x10000000);
}

TEST(systemSetup, TestSetRegulatorVoltageScale)
{
    uint32_t virtualPWR_ControlRegister = 0x0;
    uint32_t virtualRCC_APB1ClockEnableRegister = 0x0;
    systemSetup(&virtualRCC_APB1ClockEnableRegister, &virtualPWR_ControlRegister, RCC_APB1LPENR_PWRLPEN, PWR_CR_VOS_1);
    CHECK_EQUAL(virtualPWR_ControlRegister, 0x00008000);
}

TEST(systemSetup, WaitUntilHSIReady)
{
//    FAIL("Fail is actually producing an error.\n");
}

TEST(systemSetup, WaitUntilHSIReady2)
{
//    FAIL("Fail is actually producing an error2.\n");
}
