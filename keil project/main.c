#include "tm4c123gh6pm_a.h"
#include "Tm4c123GH6pm.h"
#include "motor.h"
#include "uart.h"
#include "adc.h"
#include "PWM.h"

int main(void)
{
int8_t data_btn,upper,lower;
int duty_cycle,data_adc,temp;
	int i;

uartInitM4_BTN(9600);
uartInitM3_ADC(9600);
motor_init();
ADC0_init();
//PWM1_init (3);
//led_init_pwm (3);

while(1)
{
	
//	if((UART4->FR & 0x10) == 0)
//	{
//		data_btn=UART_RECIEVE_BTN();
//		switch(data_btn)
//		{	
//			case'#':Rotate(negative,30);
//				break;
//			case'$':Rotate(positive,30);
//			break;
//		}
//	}
////		 if((UART3->FR & 0x10) == 0)
////	{
////		data_adc=UART_RECIEVE_ADC();
////		data_adc=data_adc<<4;
////		while((UART3->FR & 0x10) != 0);
////		data_adc|=UART_RECIEVE_ADC();
////		duty_cycle=(data_adc)/4096;
////		SetDutyCycle(3 ,duty_cycle);
////	}
for(i=0;i<5;i++)
{
 temp=(100*i)+get_temp();
 upper=temp>>4;
 lower=temp&0x00f;
 UART_SEND_ADC(upper);
 UART_SEND_ADC(lower);
 delay_ms(5000);
	
}
}
}

	
//	char data;
//  uint16_t temp;
//	ADC0_init();
//	while(1)
//	{
//	  temp=get_temp();
//	}
////	SYSCTL_RCGCGPIO_R|=0X20;
////	while((SYSCTL_PRGPIO_R&0X20)==0);
////	GPIO_PORTF_DEN_R|=0X0E;
////	GPIO_PORTF_DIR_R|=0X0E;
////motor_init();
////  uartInitM4(9600);
////	while (1)
////	{
//	
//////		if((UART4->FR & 0x10) == 0)
//////		{
//////		
//////		data=UART_RECIEVE ();
//////		switch(data)
//////		{	
//////			case'#':Rotate(negative,30);
//////				break;
//////			case'$':Rotate(positive,30);
//////			break;
//////		}
//////	}
////		Rotate(positive,30);
////	}
	

//void SystemInit(void)
//{

//SCB->CPACR |=0x00f00000 ;
//}
