#include "unity_fixture.h"
#include <systemSetup/rccSetup.h>
//#include "RunTimeErrorStub.h"

TEST_GROUP(rccSetupGroup);

TEST_SETUP(rccSetupGroup)
{
	;
}

TEST_TEAR_DOWN(rccSetupGroup)
{
	;
}

TEST(rccSetupGroup, SelectClockHSI)
{
	uint32_t temp;
	uint32_t virtualRCC_CR = 0x0000FF81U;		//Default value for RCC_CR is 0x0000XX81
	rccSetup(&virtualRCC_CR, RCC_CR_HSION);	//Setup clock
	temp = virtualRCC_CR | 0x1U;				//HSIRDY must be set and HSION
	TEST_ASSERT_EQUAL_HEX32(temp, virtualRCC_CR);
}

