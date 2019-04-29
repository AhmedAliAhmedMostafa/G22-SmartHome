#ifndef __PWM_H__
#define __PWM_H__

#include <stdint.h>

void PWM5_3_G2 (void);
void PWM6_3_G3 (void);
void PWM7_3_G3 (void); 
void PWM1_init (uint8_t  pin_index) ;
void SetDutyCycle(uint8_t pin_index ,uint8_t duty_cycle );


#endif