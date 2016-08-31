#include "unity_fixture.h"

TEST_GROUP_RUNNER(FirstGroup)
{
	RUN_TEST_CASE(FirstGroup, FirstTest);
	RUN_TEST_CASE(FirstGroup, SecondTest);
}
