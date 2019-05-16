#include "swicth.h"

#define GPIO_PF0_M					0x01U	
#define GPIO_PF4_M					0x10U	

void SW1_Init(void)
{
	volatile unsigned long delay;
 	 SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;  
  	delay = SYSCTL_RCGCGPIO_R;        				
  	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;   			  
  	GPIO_PORTF_CR_R |= GPIO_PF0_M		;				 
  	GPIO_PORTF_AMSEL_R &= GPIO_PF0_M;					
  	GPIO_PORTF_PCTL_R &= ~GPIO_PCTL_PF0_M;  
  	GPIO_PORTF_AFSEL_R &= GPIO_PF0_M;					
	GPIO_PORTF_DIR_R &= GPIO_PF0_M;					
	GPIO_PORTF_PUR_R |= GPIO_PF0_M;					
  	GPIO_PORTF_DEN_R |= GPIO_PF0_M;					
}

void SW2_Init(void){
	volatile unsigned long delay;
	  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;  
  	delay = SYSCTL_RCGCGPIO_R;        				
  	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;   			  
  	GPIO_PORTF_CR_R |= GPIO_PF4_M;          	 
  	GPIO_PORTF_AMSEL_R &= ~GPIO_PF4_M;      
  	GPIO_PORTF_PCTL_R &= ~GPIO_PCTL_PF4_M;  
	  GPIO_PORTF_AFSEL_R &= ~GPIO_PF4_M;      
	GPIO_PORTF_DIR_R &= ~GPIO_PF4_M;
	GPIO_PORTF_PUR_R |= GPIO_PF4_M;
	  GPIO_PORTF_DEN_R |= GPIO_PF4_M;			
}

unsigned char SW1_Input(void)
{
	return GPIO_PORTF_DATA_R&GPIO_PF0_M;
}

unsigned char SW2_Input(void){
	return GPIO_PORTF_DATA_R&GPIO_PF4_M;
}