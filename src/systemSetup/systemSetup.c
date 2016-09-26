#include <stdint.h>
#include "systemSetup.h"

void systemSetup(uint32_t * address, pll_source_mux_type pll_source_mux)
{
	if (pll_source_mux == HSI)
	{
		*address = *address | 0x000000001U;
	}
}
