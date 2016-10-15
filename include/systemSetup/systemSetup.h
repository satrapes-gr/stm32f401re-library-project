#ifndef SYSTEMSETUP_H
#define SYSTEMSETUP_H

typedef enum {HSI, HSE} clock_source_type;

void systemSetup(uint32_t * address, clock_source_type clock_source);

#endif /* SYSTEMSETUP_H */
