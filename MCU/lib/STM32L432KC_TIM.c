// Luke Summers lsummers@g.hmc.edu
// implementation for timer functions

#include "STM32L432KC_TIM.h"

void enableCounter(TIM_TypeDef* TIM) {
  TIM->CR1 |= (1 << 0);
}

void disableCounter(TIM_TypeDef* TIM) {
  TIM->CR1 &= ~(1 << 0);
}

void resetFlag(TIM_TypeDef* TIM) {
  TIM->SR &= ~(1 << 0);
}

void resetCount(TIM_TypeDef* TIM) {
  TIM->CNT = 0;
}

void setPrsc(TIM_TypeDef *TIM, uint32_t val) {
  TIM->PSC = val;
}

void setArr(TIM_TypeDef *TIM, uint32_t val) {
  TIM->ARR = val;
}

void enableCCInt(TIM_TypeDef* TIM) {
  TIM->DIER |= (1 << 1);
}

void enableCC(TIM_TypeDef* TIM) {
  TIM->CCER |= (1 << 0);
}

void setMode(TIM_TypeDef* TIM, int mode) {
  if (mode == 1) {
    TIM->CCMR1 |= (1 << 0);
  } 
  if (mode == 2) {
    TIM->CCMR1 |= (1 << 1);
  }
  if (mode == 3) {
    TIM->CCMR1 |= (0b11 << 0);
  }
}

void pollingDelay(TIM_TypeDef* TIM, int ms) {
  setArr(TIM, ms);
  resetFlag(TIM);
  resetCount(TIM);
  // wait on counter overflow
  while (!(TIM->SR)) {}
}

void genSqWave(int freq, int dur, int pin, GPIO_TypeDef* GPIO, TIM_TypeDef *TIM_1, TIM_TypeDef* TIM_2) {
  if (freq == 0) {
    pollingDelay(TIM1, dur);
  } else {
    setArr(TIM1, dur);
    setArr(TIM2, 1000000 / (2 * freq));
    resetFlag(TIM1);
    resetFlag(TIM2);
    resetCount(TIM1);
    resetCount(TIM2);
    // wait on counter overflow
    while (!(TIM1->SR)) {
      digitalWrite(pin, 1, GPIO);
      // wait on counter overflow
      while (!(TIM2->SR)) {}
      resetFlag(TIM2);
      digitalWrite(pin, 0, GPIO);
      // wait on counter overflow
      while (!(TIM2->SR)) {}
      resetFlag(TIM2);
    }
  }
}