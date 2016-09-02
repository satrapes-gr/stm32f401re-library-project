#include "unity_fixture.h"

TEST_GROUP_RUNNER(UARTDriverGroup)
{
	RUN_TEST_CASE(UARTDriverGroup, FirstTest);
	RUN_TEST_CASE(UARTDriverGroup, SecondTest);
}
