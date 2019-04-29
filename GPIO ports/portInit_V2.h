#include"TM4C123GH6PM.h"
void PortInit (uint8_t portIndex) // assume port [A:F] as [0:5]
	{
		if     (portIndex==0){GPIOA->LOCK=0x4C4F434B;SYSCTL->RCGCGPIO|=0X01;/*GPIOA->DATA|=0X0;*/GPIOA->DEN=0XFF;return;}
		else if(portIndex==1){GPIOB->LOCK=0x4C4F434B;SYSCTL->RCGCGPIO|=0X02;/*GPIOB->DATA|=0X0;*/GPIOB->DEN=0XFF;return;}
		else if(portIndex==2){GPIOC->LOCK=0x4C4F434B;SYSCTL->RCGCGPIO|=0X04;/*GPIOC->DATA|=0X0;*/GPIOC->DEN=0XFF;return;}
		else if(portIndex==3){GPIOD->LOCK=0x4C4F434B;SYSCTL->RCGCGPIO|=0X08;/*GPIOD->DATA|=0X0;*/GPIOD->DEN=0XFF;return;}
		else if(portIndex==4){GPIOE->LOCK=0x4C4F434B;SYSCTL->RCGCGPIO|=0X10;/*GPIOE->DATA|=0X0;*/GPIOE->DEN=0XFF;return;}
		else if(portIndex==5){GPIOF->LOCK=0x4C4F434B;SYSCTL->RCGCGPIO|=0X20;/*GPIOF->DATA|=0X0;*/GPIOF->DEN=0XFF;return;}
		else {return;}
	}