#include "unity_fixture.h"
#include "UARTDriver.h"
//#include "RunTimeErrorStub.h"

TEST_GROUP(UARTDriverGroup);

TEST_SETUP(UARTDriverGroup)
{
	;
}

TEST_TEAR_DOWN(UARTDriverGroup)
{
	;
}

TEST(UARTDriverGroup, AllPeripheralsOnRCCAPB1AreDisconnectedOnCreate)
{
	uint32_t virtual_RCC_APB1ENR= 0x00000000;
	UARTDriver_Create(&virtual_RCC_APB1ENR);
	TEST_ASSERT_EQUAL_HEX32(0, virtual_RCC_APB1ENR);

}

TEST(UARTDriverGroup, Fail)
{
	TEST_ASSERT_EQUAL(0, 0);
}


