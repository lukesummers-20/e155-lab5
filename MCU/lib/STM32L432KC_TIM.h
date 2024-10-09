// Luke Summers lsummers@g.hmc.edu
// Header for timer functions

#ifndef STM32L432KC_TIM_H
#define STM32L432KC_TIM_H

#include <stdint.h> // Include stdint header 
#include "STM32L432KC_GPIO.h"


///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void enableCounter(TIM_TypeDef* TIM);
void disableCounter(TIM_TypeDef* TIM);
void resetFlag(TIM_TypeDef* TIM);
void resetCount(TIM_TypeDef* TIM);
void setPrsc(TIM_TypeDef* TIM, uint32_t val);
void setArr(TIM_TypeDef* TIM, uint32_t val);
void enableCCInt(TIM_TypeDef* TIM);
void enableCC(TIM_TypeDef* TIM);
void setMode(TIM_TypeDef* TIM, int mode);
void pollingDelay(TIM_TypeDef* TIM, int ms);
void genSqWave(int freq, int dur, int pin, GPIO_TypeDef* GPIO, TIM_TypeDef *TIM_1, TIM_TypeDef* TIM_2);

#endif
