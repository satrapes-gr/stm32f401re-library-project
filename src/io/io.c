#include "io.h"

void io_write(ioAddress address, ioData data)
{
	ioData * p = 0;
	*(p + address) = data;
}

ioData io_read(ioAddress address)
{
	ioData * p = 0;
	return *(p + address);
}
