// Luke Summers lsummers@g.hmc.edu
// header file for GPIO

#ifndef STM32L432KC_GPIO_H
#define STM32L432KC_GPIO_H

#include <stdint.h>
#include "stm32l432xx.h"

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

// Arbitrary GPIO functions for pinMode()
#define GPIO_INPUT  0
#define GPIO_OUTPUT 1
#define GPIO_ALT    2
#define GPIO_ANALOG 3

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void pinMode(int pin, int function, GPIO_TypeDef* GPIO);

int digitalRead(int pin, GPIO_TypeDef* GPIO);

void digitalWrite(int pin, int val, GPIO_TypeDef* GPIO);

void togglePin(int pin, GPIO_TypeDef* GPIO);

void enablePullUp(int pin, GPIO_TypeDef* GPIO);

#endif