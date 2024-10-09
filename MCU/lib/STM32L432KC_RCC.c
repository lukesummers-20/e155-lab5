// Luke Summers lsummers@g.hmc.edu
// implementation for RCC

#include "stm32l432xx.h"

void enableTimer(int num) {
  switch(num) {
    case 1: RCC->APB2ENR |= (1 << 11);
    case 2: RCC->APB1ENR1 |= (1 << 0);
    case 6: RCC->APB1ENR1 |= (1 << 4);
    case 7: RCC->APB1ENR1 |= (1 << 5);
    case 15: RCC->APB2ENR |= (1 << 16);
    case 16: RCC->APB2ENR |= (1 << 17);
  }
}

void enableGPIO(int num) {
  switch(num) {
    case 0: // GPIO A
      RCC->AHB2ENR |= (1 << 0);
    case 1: // GPIO B
      RCC->AHB2ENR |= (1 << 1);
    case 2: // GPIO C
      RCC->AHB2ENR |= (1 << 2);
    case 3: // GPIO D
      RCC->AHB2ENR |= (1 << 3);
    case 4: // GPIO E
      RCC->AHB2ENR |= (1 << 4);
  }
}