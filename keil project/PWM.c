#include "tm4c123gh6pm_a.h" 
#include "stdint.h"
#include "PWM.h"


void PWM5_3_G2 (void)  // for pf1
{
	PWM1_2_CTL_R = 0x00000000 ;
	PWM1_2_GENA_R = 0x0000008C; // Drive PWM High at reload value and drive it to zero when it matches CMP
	PWM1_2_LOAD_R = 2500 - 1; // 500 Hz
	PWM1_2_CMPA_R = 2498 ; // 0% Duty Cycle 
	PWM1_2_CTL_R = PWM_0_CTL_ENABLE;
	PWM1_ENABLE_R  = PWM_ENABLE_PWM5EN; // M1PWM5 (PF1) 
}

void PWM6_3_G3 (void)  // for pf2
{
	PWM1_3_CTL_R = 0x00000000 ;
	PWM1_3_GENA_R = 0x0000008C; // Drive PWM High at reload value and drive it to zero when it matches CMP
	PWM1_3_LOAD_R = 2500 - 1; // 500 Hz
	PWM1_3_CMPA_R = 2498 ; // 0% Duty Cycle 
	PWM1_3_CTL_R = PWM_0_CTL_ENABLE;
	PWM1_ENABLE_R  = PWM_ENABLE_PWM6EN; // M1PWM6 (PF2) 
}

void PWM7_3_G3 (void)  // for pf3
{
	PWM1_3_CTL_R = 0x00000000 ;
	PWM1_3_GENB_R = 0x0000008C; // Drive PWM High at reload value and drive it to zero when it matches CMP
	PWM1_3_LOAD_R = 4000; // 500 Hz
	PWM1_3_CMPA_R = 4000-1 ; // 0% Duty Cycle 
	PWM1_3_CTL_R = 1;
	PWM1_ENABLE_R  = 0x80; // M1PWM7 (PF3) 
}


void portf_init()
{
	SYSCTL_RCGCGPIO_R|=0x20;
	while((SYSCTL_PRGPIO_R&0x20)==0);
	GPIO_PORTF_DEN_R|=0x08;
//	GPIO_PORTF_DIR_R|=0x08;
	GPIO_PORTF_AFSEL_R|=0x08;
	GPIO_PORTF_PCTL_R&=~0xf000;
	GPIO_PORTF_PCTL_R|=0x5000;
}
void PWM1_init (uint8_t  pin_index)
{
	/*from the data sheet */
	//SYSCTL_RCGC0_R |= 0x00100000;   // Enable the PWM clock by writinga value of 0x0010.0000 to the RCGC0 register 
	
	SYSCTL_RCGCPWM_R |= SYSCTL_RCGCPWM_R1; // PWM Module 1 Run Mode Clock
                                               // Gating Control
	
	SYSCTL_RCC_R |= 0x00100000;  // Enable PWM Clock Divisor
	SYSCTL_RCC_R |= 0x000A00000;  // PWM Clock = 1.25 MHz (20/16)
	portf_init();
	// pwm1 generator 3 (pf2 , pf3) and generator 2 for pf1
	switch (pin_index)
	
		{
			case 1 : PWM5_3_G2();break;
			
		   case 2 : PWM6_3_G3();break;
			
			case 3 :PWM7_3_G3();break;
		}
	
}


void SetDutyCycle(uint8_t pin_index ,uint8_t duty_cycle )
{
	if(duty_cycle==100){PWM1_3_CMPA_R ==1;}
	else if(duty_cycle<=0){PWM1_3_CMPA_R =8000-2;}
		
	else
	{
	switch (pin_index)
	
				{
								case 1 : PWM1_2_CMPA_R = (uint16_t)(2500 * (1 - (duty_cycle / 100.0)) - 1);		break;
								case 2 : PWM1_3_CMPA_R = (uint16_t)(2500 * (1 - (duty_cycle / 100.0)) - 1);		break;
								case 3 : PWM1_3_CMPA_R = (uint16_t)(4000 * (1 - (duty_cycle / 100.0)) - 1);		break;
				}
		}
}
	



