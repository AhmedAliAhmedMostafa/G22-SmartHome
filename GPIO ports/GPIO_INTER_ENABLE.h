#include"TM4C123GH6PM.h"
typedef  enum  {INT_ENABLE,INT_DISABLE}INT_STATE;			// THIS FUNC WILL BE USED IF PUSH BUTTONS ARE INTERRUPT DRIVEN
void GPIO_INT_INIT(uint8_t portIndex,uint8_t pins_mask,INT_STATE INT)	// TO ENABLE/DISABLE EXTERNAL INTERRUPT FED THROUGH ANY GPIO PORT
{									// ex:IF YOU HAVE A PUSH BUTTON CONNECTED TO PORTA PIN 0 
if(INT==INT_ENABLE)							// THEN , YOU NEED TO SET THAT PIN DIRCTION TO INPUT AND IN THE SAME WAY
		{							// (AND THE SAME MASK) USE THIS FUNC TO ENABLE INTERRUPT
			if     (portIndex==0){GPIOA->ICR|=pins_mask;GPIOA->IM|=pins_mask;NVIC->ISER[0] |= 1   ;}
			else if(portIndex==1){GPIOB->ICR|=pins_mask;GPIOB->IM|=pins_mask;NVIC->ISER[0] |= 1>>1;}
			else if(portIndex==2){GPIOC->ICR|=pins_mask;GPIOC->IM|=pins_mask;NVIC->ISER[0] |= 1>>2;}
			else if(portIndex==3){GPIOD->ICR|=pins_mask;GPIOD->IM|=pins_mask;NVIC->ISER[0] |= 1>>3;}
			else if(portIndex==4){GPIOE->ICR|=pins_mask;GPIOE->IM|=pins_mask;NVIC->ISER[0] |= 1>>4;}
			else if(portIndex==5){GPIOF->ICR|=pins_mask;GPIOF->IM|=pins_mask;NVIC->ISER[0] |= 0x40000000;}
			__enable_irq();
		}
	else 
		{
			if     (portIndex==0){GPIOA->IM&=~pins_mask;NVIC->ICER[0] |= 1		;}
			else if(portIndex==1){GPIOB->IM&=~pins_mask;NVIC->ICER[0] |= 1>>1       ;}
			else if(portIndex==2){GPIOC->IM&=~pins_mask;NVIC->ICER[0] |= 1>>2	;}
			else if(portIndex==3){GPIOD->IM&=~pins_mask;NVIC->ICER[0] |= 1>>3	;}
			else if(portIndex==4){GPIOE->IM&=~pins_mask;NVIC->ICER[0] |= 1>>4	;}
			else if(portIndex==5){GPIOF->IM&=~pins_mask;NVIC->ICER[0] |= 0x40000000;}
			__disable_irq();
		}
}
