#include "motor.h"
#include "tm4c123gh6pm_a.h"
const char sequence[]={0x3,0X9,0xc,0x6};

void delay_ms(int delay)
{
	int i,j;
	for(i=0;i<delay;i++)
	{
		for(j=0;j<3180;j++)
		{}
	}
}
void Rotate(Rotation_Dirction dir,int degree)
{
  int num_steps;
	int i,j;
	num_steps=degree/motor_step;
  for(j=0;j<num_steps;j++)
	{	
		for(i=0;i<4;i++)
		{
			if(dir==positive)
			{
				GPIO_PORTB_DATA_R=(GPIO_PORTB_DATA_R&~0x0f)|sequence[3-i];
			}
			else if(dir==negative)
			{
				GPIO_PORTB_DATA_R=(GPIO_PORTB_DATA_R&~0x0f)|sequence[i];
			}
			delay_ms(10);
		}
	}
}
void motor_init(void)
{
	SYSCTL_RCGCGPIO_R|=0x02;
	while((SYSCTL_PRGPIO_R&0X02)==0);
	GPIO_PORTB_DEN_R|=0X0F;
	GPIO_PORTB_DIR_R|=0X0F;
}
