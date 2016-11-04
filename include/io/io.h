#ifndef IO_MODULE_H
#define IO_MODULE_H

#include <stdint.h>

typedef uint32_t ioAddress;
typedef uint32_t ioData;

void io_write(ioAddress address, ioData data);
ioData io_read(ioAddress address);

#endif		/* IO_MODULE_H */
