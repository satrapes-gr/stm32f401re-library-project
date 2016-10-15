#include "unity_fixture.h"
#include "systemSetup.h"
//#include "RunTimeErrorStub.h"

TEST_GROUP(systemSetupGroup);

TEST_SETUP(systemSetupGroup)
{
	;
}

TEST_TEAR_DOWN(systemSetupGroup)
{
	;
}

TEST(systemSetupGroup, SelectClockHSI)
{
	uint32_t virtualRCC_CR = 0xFFFFFFFF;
	systemSetup(&virtualRCC_CR);
	TEST_ASSERT_EQUAL(RCC_CR_HSION, 0x00000001);
}


