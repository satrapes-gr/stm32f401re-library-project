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
	TEST_ASSERT_EQUAL(0, 0x00000001);
}


