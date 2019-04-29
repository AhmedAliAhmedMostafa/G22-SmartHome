#include"TM4C123GH6PM.h"
typedef  enum  {EDGE_TRIGGERED,LEVEL_TRIGGERED}TRIGGER_STATE;
typedef  enum  {LOW_FALL,HIGH_RISE}ACTION_TIME;
void INT_STATE_ACTION(uint8_t portIndex,uint8_t pins_mask,TRIGGER_STATE TRIGGER,ACTION_TIME ACTION)	// WILL BE USED AFTER GPIO_INT_INIT FUNC
																																								// <=== THIS FUNC IS MORE OF LOOK_UP_TABLE THAN OF REAL ALGORITHM
{																																								// SET INTERRUPT TRRIGER TYPE(LEVEL/EDGE) AND WHICH INTERVAL
	if(TRIGGER==EDGE_TRIGGERED)																										// {HIGH/LOW OR FALLING/RISING EDGES} THIS IS DONE FOR EVERY 
																																								// PORT WITH THE GIVEN MASK 
	{																																							// NOTE: MAKE SURE THAT GPIO_INT_INIT FUNC IS MADE FOR THE SAME PINS
		if(ACTION==HIGH_RISE)
		{
			if		 (portIndex==0){GPIOA->IS&=~pins_mask ;GPIOA->IEV|=pins_mask;}
			else if(portIndex==1){GPIOB->IS&=~pins_mask ;GPIOB->IEV|=pins_mask;}
			else if(portIndex==2){GPIOC->IS&=~pins_mask ;GPIOC->IEV|=pins_mask;}
			else if(portIndex==3){GPIOD->IS&=~pins_mask ;GPIOD->IEV|=pins_mask;}
			else if(portIndex==4){GPIOE->IS&=~pins_mask ;GPIOE->IEV|=pins_mask;}
			else if(portIndex==5){GPIOF->IS&=~pins_mask ;GPIOF->IEV|=pins_mask;}
		}
		if(ACTION==LOW_FALL)
		{
			if		 (portIndex==0){GPIOA->IS&=~pins_mask ;GPIOA->IEV&=~pins_mask;}
			else if(portIndex==1){GPIOB->IS&=~pins_mask	;GPIOB->IEV&=~pins_mask;}
			else if(portIndex==2){GPIOC->IS&=~pins_mask ;GPIOC->IEV&=~pins_mask;}
			else if(portIndex==3){GPIOD->IS&=~pins_mask ;GPIOD->IEV&=~pins_mask;}
			else if(portIndex==4){GPIOE->IS&=~pins_mask ;GPIOE->IEV&=~pins_mask;}
			else if(portIndex==5){GPIOF->IS&=~pins_mask ;GPIOF->IEV&=~pins_mask;}
		}
	}
	if(TRIGGER==LEVEL_TRIGGERED)
	{
		if(ACTION==HIGH_RISE)
		{
			if		 (portIndex==0){GPIOA->IS|=pins_mask ;GPIOA->IEV|=pins_mask;}
			else if(portIndex==1){GPIOB->IS|=pins_mask ;GPIOB->IEV|=pins_mask;}
			else if(portIndex==2){GPIOC->IS|=pins_mask ;GPIOC->IEV|=pins_mask;}
			else if(portIndex==3){GPIOD->IS|=pins_mask ;GPIOD->IEV|=pins_mask;}
			else if(portIndex==4){GPIOE->IS|=pins_mask ;GPIOE->IEV|=pins_mask;}
			else if(portIndex==5){GPIOF->IS|=pins_mask ;GPIOF->IEV|=pins_mask;}
		}
		if(ACTION==LOW_FALL)
		{
			if		 (portIndex==0){GPIOA->IS|=pins_mask ;GPIOA->IEV&=~pins_mask;}
			else if(portIndex==1){GPIOB->IS|=pins_mask ;GPIOB->IEV&=~pins_mask;}
			else if(portIndex==2){GPIOC->IS|=pins_mask ;GPIOC->IEV&=~pins_mask;}
			else if(portIndex==3){GPIOD->IS|=pins_mask ;GPIOD->IEV&=~pins_mask;}
			else if(portIndex==4){GPIOE->IS|=pins_mask ;GPIOE->IEV&=~pins_mask;}
			else if(portIndex==5){GPIOF->IS|=pins_mask ;GPIOF->IEV&=~pins_mask;}
		}
	}
}
