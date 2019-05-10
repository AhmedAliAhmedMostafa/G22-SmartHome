#ifndef __PWM_H__
#define __PWM_H__

#include <stdint.h>

#define GPIO_PF1_M	0x02
#define GPIO_PF2_M	0x04
#define GPIO_PF3_M	0x08

void PWM5_3_G2 (void);
void PWM6_3_G3 (void);
void PWM7_3_G3 (void); 
void PWM1_init (uint8_t  pin_index) ;
void SetDutyCycle(uint8_t pin_index ,uint8_t duty_cycle );
void led_init_pwm (uint8_t pin_index) ;

#endif
