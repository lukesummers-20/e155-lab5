#include <stm32l432xx.h>
#include "../lib/GPIO.h"
#include "../lib/RCC.h"
#include "../lib/TIM67.h"
#include <stdio.h>

//pulses per loop for calculations when TIM1 counter resets
#define LOOP_OFFSET ((int) 4800)

//counts per rotation
#define COUNTS_PER_ROTATION ((int) 480)

//time between each interupt, which is how often the distance moved is checked
#define TIME_STEP ((double) 0.250)

int cur, curHold, last, update, direction = 0;

//calculates the distance between x0 and x1
// param: x0 - second to most recent position
//        x1 - most recent position
//        upCounting - 1 if counter is up counting, 0 if down
//return: distance between x0 and x1 in counts
double delta(double x0, double x1, int upCounting) {
  if (x0 == x1) {
    return 0;
  } else {
    if (upCounting && (x1 < x0)) {
      return (x1 -x0) + LOOP_OFFSET;
    }
    if (!(upCounting) && (x1 > x0)) {
      return (x1 - x0) - LOOP_OFFSET; 
    }
    return x1 - x0;
  }
}




int main(void) {
  //encoder pins
  int pinS1 = 8;
  int pinS2 = 9;

  double dist, rps, f1, f2, f3;

  //GPIOA setup
  
  //enable GPIOA
  enableGPIO(0);

   //sets pin 8 to af
  pinMode(pinS1, GPIO_ALT, GPIOA);

  //sets pin 8 to AF 1, tim1 ch1
  GPIOA->AFR[1] |= (1 << 0);

  //sets pin 9 to af
  pinMode(pinS2, GPIO_ALT, GPIOA);

  //sets pin 9 to AF 1, tim1 ch2
  GPIOA->AFR[1] |= (1 << 4);



  //TIM7 setup

  enableTimer(7);

  //prescale tim7 to run at 1 khz
  TIM7->PSC = 4000;

  TIM7->ARR = TIME_STEP * 1000;

  TIM7->DIER |= (1 << 0);



  //TIM1 setup

  //enable TIM1
  enableTimer(1);

  //sets tim1 to encoder mode 3
  TIM1->SMCR |= (0b11 << 0);

  //maps IC1 to TI1
  TIM1->CCMR1 |= (1 << 0);

  //maps IC2 to TI2
  TIM1->CCMR1 |= (1 << 8);

  TIM1->ARR = LOOP_OFFSET;

  //flipping polarity so positive direction is when the motors red terminal is powered
  TIM1->CCER |= (1 << 1);

  //enable interupts globally and TIM7 interupt
  __enable_irq();
  NVIC->ISER[1] |= (1 << (TIM7_IRQn - 32));

  //starting timer counters
  enableCounter(TIM1);
  enableCounter(TIM7);

  while(1) {
    if (update) {
      dist = delta(last, cur, !(TIM1->CR1 & (1 << 4)));
      f3 = f2;
      f2 = f1;
      f1 = dist / (TIME_STEP * COUNTS_PER_ROTATION);
      rps = (f1 + f2 + f3) / 3;
      printf("Rev per second: %f\n", rps);
      update = 0;
    }
  }

  return 0;
}

//TIM7 ISR Handler
//   captures encoder position, tells main to calc a new frequency
void TIM7_IRQHandler(void){
  cur = TIM1->CNT;
  last = curHold;
  curHold = cur;
  TIM7->SR &= ~(1 << 0);
  update = 1;
}