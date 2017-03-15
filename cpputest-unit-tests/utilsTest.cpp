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
#include "utils.h"
#include "MockIO.h"
#include <stdio.h>
}

#define MOCK_EXPECTATIONS_SIZE (100)
#define RANDOM_VALUE (0x12345678)
#define ALL_ONES (0xFFFFFFFF)
#define BIT_MASK_BIT0 (0x1)

TEST_GROUP(utilsSetup)
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
 * Test utils functions
 */
IGNORE_TEST(utilsSetup, setBit)
{
    bool result;
    ioData virtualRegister = (ioData) ALL_ONES;

    result = __setBitMask(&virtualRegister, BIT_MASK_BIT0);

    CHECK_EQUAL(true, result);
}
