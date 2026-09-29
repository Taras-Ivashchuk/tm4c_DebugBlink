/*
The program demonstrates functional debugging.

The program should blink the GREEN LED at 5HZ, i.e 0.1 sec on - 0.1 sec off.
The time array records the elapsed time between toggles.
We must ensure that the delay between the toggles is close to 0.1 sec.
Output: PF3 - Green LED

Expected results for the delay function(you results may differ):
time[1] = time[2] = time[3] = 1920050 (ticks)
one_tick_period = 1 / 16 000 000 = 62.5 ns
time_elapsed = 62.5 ns * 1920050 / 1 000 000 000 ns/sec =  0,12000125 sec ~~ 0.1 sec

*/

#include "TM4C123GH6PM.h"

#define LED (1 << 3U)

// prototypes
void initGPIOF(void);
void initSysTick(void);
void delay(void);

 unsigned int time[50];

int main(void) {
  initGPIOF();
  initSysTick();
  
 
  unsigned int now;
  unsigned int last;
  unsigned int i = 0;

  last = SysTick->VAL; // read the start time

  while (1) {
    GPIOF->DATA_Bits[LED] ^= LED;
    now = SysTick->VAL; // read the end time
    if (i < 50) {
      time[i] = (last - now) & 0x00FFFFFF;
      last = now;
      ++i;
    }
    delay();
  }
  // return 0; // unreachable code
}

void initGPIOF(void) {
  // enable clocking for  GPIOF
  SYSCTL->RCGCGPIO |= (1 << 5U);

  // dummy read to add small delay before clocking activates
  volatile unsigned long delay = SYSCTL->RCGCGPIO;

  // disable analog functions for pin 1
  GPIOF->AMSEL &= ~(LED);

  // enable direction
  GPIOF->DIR |= LED; // as output

  // no alternate functions
  GPIOF->AFSEL &= ~LED;
  GPIOF->PCTL &= ~LED;

  // enable digital pins
  GPIOF->DEN |= LED;
}

void initSysTick(void) {
  SysTick->CTRL = 0x0;        // disable Systick
  SysTick->VAL = 0x0;         // clear the counter
  SysTick->LOAD = 0x00FFFFFF; // set the maximum value
  SysTick->CTRL = 0x00000005; // source the Systick with core clock
}

void delay(void) {
  volatile unsigned long time = 160000;
  while (time)
    --time;
}

// needed for startup_TM4C123GH6PM.c
__attribute__((naked)) void assert_failed(char const *file, int line) {
  /* TBD: damage control */
  NVIC_SystemReset(); /* reset the system */
}
