#include "unity_fixture.h"

TEST_GROUP_RUNNER(UARTDriverGroup)
{
	RUN_TEST_CASE(UARTDriverGroup, AllPeripheralsOnRCCAPB1AreDisconnectedOnCreate);
	RUN_TEST_CASE(UARTDriverGroup, Fail);
}

