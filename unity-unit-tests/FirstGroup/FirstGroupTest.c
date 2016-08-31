#include "unity_fixture.h"
#include "FirstGroup.h"
//#include "RunTimeErrorStub.h"

TEST_GROUP(FirstGroup);

TEST_SETUP(FirstGroup)
{
	;
}

TEST_TEAR_DOWN(FirstGroup)
{
	;
}

TEST(FirstGroup, FirstTest)
{
	TEST_ASSERT_TRUE(add(1,1) == 2);
}

TEST(FirstGroup, SecondTest)
{
	TEST_ASSERT_TRUE(add(1,1) == 3);
}
