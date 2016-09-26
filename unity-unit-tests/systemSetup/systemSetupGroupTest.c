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

TEST(systemSetupGroup, SelectPLLSource)
{
	uint32_t temp;
	uint32_t virtualRCC_CR = 0xffffffff;
	pll_source_mux_type pll_source_mux = HSI;
	systemSetup(&virtualRCC_CR, pll_source_mux);
	temp = virtualRCC_CR & 0x00000001;
	TEST_ASSERT_EQUAL(temp, 0x00000001);
}


