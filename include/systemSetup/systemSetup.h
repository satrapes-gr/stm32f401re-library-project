#ifndef SYSTEMSETUP_H
#define SYSTEMSETUP_H

typedef enum {HSI, HSE} pll_source_mux_type;

void systemSetup(uint32_t * address, pll_source_mux_type pll_source_mux);

#endif /* SYSTEMSETUP_H */
