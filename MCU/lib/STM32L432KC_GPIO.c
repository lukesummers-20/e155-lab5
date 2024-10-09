// Luke Summers lsummers@g.hmc.edu
// implementation file for GPIO

#include "STM32L432KC_GPIO.h"

void pinMode(int pin, int function, GPIO_TypeDef* GPIO) {
    switch(function) {
        case GPIO_INPUT:
            GPIO->MODER &= ~(0b11 << 2*pin);
            break;
        case GPIO_OUTPUT:
            GPIO->MODER |= (0b1 << 2*pin);
            GPIO->MODER &= ~(0b1 << (2*pin+1));
            break;
        case GPIO_ALT:
            GPIO->MODER &= ~(0b1 << 2*pin);
            GPIO->MODER |= (0b1 << (2*pin+1));
            break;
        case GPIO_ANALOG:
            GPIO->MODER |= (0b11 << 2*pin);
            break;
    }
}

int digitalRead(int pin, GPIO_TypeDef* GPIO) {
    return ((GPIO->IDR) >> pin) & 1;
}

void digitalWrite(int pin, int val, GPIO_TypeDef* GPIO) {
    if (val) {
        GPIO->ODR |= (1 << pin);
    } else {
        GPIO->ODR &= ~(1 << pin);
    }
}

void togglePin(int pin, GPIO_TypeDef* GPIO) {
    // Use XOR to toggle
    GPIO->ODR ^= (1 << pin);
}

void enablePullUp(int pin, GPIO_TypeDef* GPIO) {
  GPIO->PUPDR |= (1 << (2 * pin));
}