#include"TM4C123GH6PM.h"
#include "tm4c123gh6pm_a.h"
#include "motor.h"
#include "uart.h"
#include "adc.h"
#include "PWM.h"

int main(void)
{
	char data;
	uart_init();
	motor_init();
	
	while (1)
	{
		if((UART0_FR_R & 0x10) == 0)
		{
			
		}
		/*code ADC*/
		
	}
	

}
