#include "tm4c123gh6pm.h" 
#include "stdint.h"
#include "PWM.h"

void led_init_pwm (uint8_t pin_index)
{
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;  	//GPIO Port F Run Mode Clock
	
	switch (pin_index)
	{
		case 1 :
			GPIO_PORTF_AFSEL_R |= GPIO_PF1_M;  //enable alternative function (pwm)
			GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFFF0F) | (GPIO_PCTL_PF1_M1PWM5); // M1PWM5 on PF1
			GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY ;
			GPIO_PORTF_DIR_R |= GPIO_PF1_M;
			GPIO_PORTF_DEN_R |= GPIO_PF1_M;
		
		case 2 :
			GPIO_PORTF_AFSEL_R |= GPIO_PF2_M;   //enable alternative function (pwm)
			GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF) | (GPIO_PCTL_PF2_M1PWM6);  //M1PWM6 on PF2
			GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY ;
			GPIO_PORTF_DIR_R |= GPIO_PF2_M;
			GPIO_PORTF_DEN_R |= GPIO_PF2_M;
		
		case 3 :
		  GPIO_PORTF_AFSEL_R |= GPIO_PF3_M;  //enable alternative function (pwm)
			GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFF0FFF) | (GPIO_PCTL_PF3_M1PWM7);  // M1PWM7 on PF3
			GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY ;
			GPIO_PORTF_DIR_R |= GPIO_PF3_M;
			GPIO_PORTF_DEN_R |= GPIO_PF3_M;

	}
}