//#include <stdint.h>
#include "systemSetup.h"

int global_uninit;
int global_init = 0;
//static int global_static_uninit;
//static int global_static_init = 0;


void systemSetup(uint32_t * address, uint32_t clock)
{
	*address |= clock;
}
