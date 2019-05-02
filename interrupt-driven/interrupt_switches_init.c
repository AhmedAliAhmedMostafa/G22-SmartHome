#include "TM4C123GH6PM.h"


void interrupt_switches_init(void){

SYSCTL_RCGCGPIO_R |= 0x20;  /* enable clock to PORTF */

 /* PORTF0 has special function, need to unlock to modify */

GPIO_PORTF_LOCK_R  = 0x4C4F434B;  /* unlock commit register */
GPIO_PORTF_CR_R = 0x01;          /* make PORTF0 configurable */
GPIO_PORTF_LOCK_R = 0;           /* lock commit register */
   /* configure PORTF for switch input*/


  GPIO_PORTF_DIR_R &= ~0x11;       /* make PORTF4 input for switch */


   GPIO_PORTF_DEN_R |= 0x1F;        /* make PORTF4-0 digital pins */
   GPIO_PORTF_PUR_R  |= 0x11;        /* enable pull up for PORTF4, 0 */


   /* configure PORTF4, 0 for falling edge trigger interrupt */

  GPIO_PORTF_IS_R  &= ~0x11;       /* make bit 4, 0 edge sensitive */
   GPIO_PORTF_IBE_R &= ~0x11;       /* trigger is controlled by IEV */
  GPIO_PORTF_IEV_R  &= ~0x11;       /* falling edge trigger */
  GPIO_PORTF_ICR_R  |= 0x11;        /* clear any prior interrupt */
  GPIO_PORTF_IM_R |= 0x11;        /* unmask interrupt */


   /* enable interrupt in NVIC and set priority to 3 */
   NVIC_PRI17_R  = 3 << 5;    /* set interrupt priority to 3 */
   NVIC_EN0_R |= 0x40000000; /* enable IRQ30 (D30 of ISER[0]) */
   __enable_irq(); /* global enable IRQs */

}
