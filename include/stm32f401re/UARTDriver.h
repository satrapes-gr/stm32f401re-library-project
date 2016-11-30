#ifndef SERIAL_H
#define SERIAL_H

#include "stm32f4xx.h"
#include <system_stm32f4xx.h>

//SERIAL_TX = PA_2
//SERIAL_RX = PA_3

void serialInit(void);
uint8_t sendChar(uint8_t ch);
uint8_t sendString(uint8_t *string);

#endif //SERIAL_H
