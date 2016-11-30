#ifndef GPIO_H
#define GPIO_H

#include <stm32f4xx.h>

#define LED_PIN 5
#define LED_ON() GPIOA->BSRR |= (1 << LED_PIN)
#define LED_OFF() GPIOA->BSRR |= (1<< (LED_PIN + 16))

void GPIOAInit();

#endif //GPIO_H
