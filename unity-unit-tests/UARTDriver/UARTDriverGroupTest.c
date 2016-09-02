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

TEST(UARTDriverGroup, FirstTest)
{
	TEST_ASSERT_TRUE(add(1,1) == 2);
}

TEST(UARTDriverGroup, SecondTest)
{
	TEST_ASSERT_TRUE(add(1,1) == 3);
}
