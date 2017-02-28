#include "unity_fixture.h"

static void RunAllTests(void)
{
	RUN_TEST_GROUP(rccSetupGroup);
//	RUN_TEST_GROUP(UARTDriverGroup);
}

int main(int argc, const char **argv)
{
	return UnityMain(argc, argv, RunAllTests);
}
