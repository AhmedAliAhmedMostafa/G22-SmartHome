#include"TM4C123GH6PM.h"
typedef  enum  {PORT_PIN_IN,PORT_PIN_OUT}Port_PinDirectionType;

//THE MASK SHOULD BE SET=1 AT THE DESIRED BITS
void Port_SetPinDirection(uint8_t portIndex,uint8_t pins_mask,Port_PinDirectionType pins_direction)
{
	if(pins_direction)
		{
			if		 (portIndex==0){GPIOA->DIR|=pins_mask;}
			else if(portIndex==1){GPIOB->DIR|=pins_mask;}
			else if(portIndex==2){GPIOC->DIR|=pins_mask;}
			else if(portIndex==3){GPIOD->DIR|=pins_mask;}
			else if(portIndex==4){GPIOE->DIR|=pins_mask;}
			else if(portIndex==5){GPIOF->DIR|=pins_mask;}
		}
	else if(!pins_direction)
		{
			if		 (portIndex==0){GPIOA->DIR&=~pins_mask;}
			else if(portIndex==1){GPIOB->DIR&=~pins_mask;}
			else if(portIndex==2){GPIOC->DIR&=~pins_mask;}
			else if(portIndex==3){GPIOD->DIR&=~pins_mask;}
			else if(portIndex==4){GPIOE->DIR&=~pins_mask;}
			else if(portIndex==5){GPIOF->DIR&=~pins_mask;}
		}
}

